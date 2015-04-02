#ifndef image_h
#define image_h

#include "common_header.h"

#ifdef __cplusplus
extern "C" {
#endif

enum enum_image_format {
	IMG_FORMAT_NULL = 0,
	IMG_FORMAT_RGBA,
	IMG_FORMAT_BGRA,
	IMG_FORMAT_RGB,
	IMG_FORMAT_BGR,
};

class image_data {
public:
	uint width;
	uint height;
	enum enum_image_format format;
	uchar *pixels;

	image_data()
		:width(0), height(0), format(IMG_FORMAT_NULL), pixels(nullptr)
	{
		
	}

	~image_data() {
		if (pixels != nullptr) {
			delete[] pixels;
			pixels = nullptr;
		}
	}
};

HEL_API void img_init_decoder();
HEL_API void img_dispose_decoder();
HEL_API int img_load_image(const char *path, image_data *data);

#ifdef __cplusplus
}
#endif

#endif