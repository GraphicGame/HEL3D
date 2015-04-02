#include "image.h"
#include "device.h"
#include "utils.h"
#include "log_internal.h"

#include <windows.h>
#include <wincodec.h>
#include <assert.h>

typedef struct image_decoder {
	IWICImagingFactory *factory;
	IWICBitmapDecoder *decoder;
	IWICBitmapFrameDecode *frame;
} image_decoder;

static image_decoder *s_decoder = nullptr;

HEL_API void img_init_decoder() {
	if (s_decoder == nullptr) {
		s_decoder = new image_decoder();
		
		HRESULT hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&s_decoder->factory)
			);
		if (hr != S_OK) {
			log_print("Failed to load WIC");
			exit(1);
		}
	}
}

HEL_API void img_dispose_decoder() {
	if (s_decoder != nullptr) {
		if (s_decoder->factory != nullptr)
			s_decoder->factory->Release();
		if (s_decoder->decoder != nullptr)
			s_decoder->decoder->Release();
		if (s_decoder->frame != nullptr)
			s_decoder->frame->Release();
		delete s_decoder;
		s_decoder = nullptr;
	}
}

static uint _get_image_stride(uint width, uint bpp) {
	assert(bpp % 8 == 0);

	uint byteCount = bpp / 8;
	uint stride = (width * byteCount + 3) & ~3;

	assert(stride % sizeof(DWORD) == 0);
	return stride;
}

//TODO : need a relative path !
HEL_API int img_load_image(const char *path, image_data *data) {
	if (s_decoder == nullptr) {
		img_init_decoder();
	}

	wchar_t *wpath = char2wchar_t(path);
	HRESULT hr = s_decoder->factory->CreateDecoderFromFilename(
			wpath,
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnDemand,
			&s_decoder->decoder
		);
	if (hr != S_OK) {
		log_print("WIC create decoder failed from the file:[%s]", {arg(path)});
		return -1;
	}

	if (s_decoder->frame != nullptr)
		s_decoder->frame->Release();

	hr = s_decoder->decoder->GetFrame(0, &s_decoder->frame);
	if (hr != S_OK) {
		log_print("WIC decode image failed! the filename is:[%s]", { arg(path) });
		return -1;
	}

	s_decoder->frame->GetSize(&data->width, &data->height);
	GUID pixel_format = { 0 };
	s_decoder->frame->GetPixelFormat(&pixel_format);

	uint stride = 0;
	if (IsEqualGUID(pixel_format, GUID_WICPixelFormat32bppRGBA)) {
		data->format = IMG_FORMAT_RGBA;
		stride = _get_image_stride(data->width, 32);
	}
	else if (IsEqualGUID(pixel_format, GUID_WICPixelFormat32bppBGRA)) {
		data->format = IMG_FORMAT_BGRA;
		stride = _get_image_stride(data->width, 32);
	}
	else if (IsEqualGUID(pixel_format, GUID_WICPixelFormat32bppBGR)) {
		data->format = IMG_FORMAT_BGR;
		stride = _get_image_stride(data->width, 32);
	}
	else if (IsEqualGUID(pixel_format, GUID_WICPixelFormat24bppRGB)) {
		data->format = IMG_FORMAT_RGB;
		stride = _get_image_stride(data->width, 24);
	}
	else if (IsEqualGUID(pixel_format, GUID_WICPixelFormat24bppBGR)) {
		data->format = IMG_FORMAT_BGR;
		stride = _get_image_stride(data->width, 24);
	}
	else {
		data->format = IMG_FORMAT_NULL;
		log_print("WIC Unsupport image format! the filename is:[%s]", {arg(path)});
		return -1;
	}

	//copy pixels.
	uint size = stride * data->height;
	if (data->pixels != nullptr)
		delete[] data->pixels;
	data->pixels = new uchar[size];
	hr = s_decoder->frame->CopyPixels(
			nullptr,
			stride,
			size,
			data->pixels
		);
	if (hr != S_OK) {
		log_print("WIC copyPixels error! the filename is:[%s]", {arg(path)});
		return -1;
	}

	return 0;
}