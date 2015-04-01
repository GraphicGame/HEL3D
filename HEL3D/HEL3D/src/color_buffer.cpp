#include "device.h"
#include "log_internal.h"

#include <assert.h>
#include <memory.h>

#include "common_header.h"
#include "GL/glew.h"

const int CB_MAX_W = 3000;
const int CB_MAX_H = 3000;

color::color() {
	
}

color::color(uint _r, uint _g, uint _b, uint _a)
:r(_r), g(_g), b(_b), a(_a) {
}

void color::modulate(float s) {
	uint tr = r;
	uint tg = g;
	uint tb = b;
	tr *= s;
	tg *= s;
	tb *= s;
	if (tr > 255 || tg > 255 || tb > 255) {
		return;
	}
	r = tr;
	g = tg;
	b = tb;
}

void color::add(const color &c) {
	r += c.r;
	r = (r > 255) ? 255 : r;
	g += c.g;
	g = (g > 255) ? 255 : g;
	b += c.b;
	b = (b > 255) ? 255 : b;
}

color_buffer::color_buffer(uint width, uint height) 
:width_(width), height_(height), dirty_(true), pixels_(nullptr)
{
	assert(width_ > 0 && width_ < CB_MAX_W);
	assert(height_ > 0 && height_ < CB_MAX_H);
	buffer_ = new color[width_ * height_];
}

color_buffer::~color_buffer() {
	delete buffer_;
}

HEL_API void color_buffer::write_color(uint x, uint y, color c) {
	if (x < 0 || x >= width_ || y < 0 || y >= height_) {
		return;
	}
	uint i = y * width_ + x;
	buffer_[i] = c;
}

void color_buffer::_write_RGBA_2_colorbuffer(image_data *img, uint start_x, uint start_y) {
	uchar *pixels = img->pixels;
	uint img_w = img->width;
	uint img_h = img->height;
	uint img_sz = img_w * img_h * 4;
	uint cb_sz = width_ * height_;

	for (uint i = 0; i < img_sz; i += 4) {
		uchar r = pixels[i];
		uchar g = pixels[i + 1];
		uchar b = pixels[i + 2];
		uchar a = pixels[i + 3];
		uint ix = i / 4 % img_w;
		uint iy = i / 4 / img_w;
		uint bx = ix + start_x;
		uint by = iy + start_y;
		uint b_index = by * width_ + bx;
		if (b_index >= cb_sz) {
			continue;
		}
		buffer_[b_index] = color(r, g, b, a);
	}
}

void color_buffer::_write_BGRA_2_colorbuffer(image_data *img, uint start_x, uint start_y) {
	uchar *pixels = img->pixels;
	uint img_w = img->width;
	uint img_h = img->height;
	uint img_sz = img_w * img_h * 4;
	uint cb_sz = width_ * height_;

	for (uint i = 0; i < img_sz; i+=4) {
		uchar b = pixels[i];
		uchar g = pixels[i + 1];
		uchar r = pixels[i + 2];
		uchar a = pixels[i + 3];
		uint ix = i / 4 % img_w;
		uint iy = i / 4 / img_w;
		uint bx = ix + start_x;
		uint by = iy + start_y;
		uint b_index = by * width_ + bx;
		if (b_index >= cb_sz) {
			continue;
		}
		buffer_[b_index] = color(r, g, b, a);
	}
}

void color_buffer::_write_RGB_2_colorbuffer(image_data *img, uint start_x, uint start_y) {
	uchar *pixels = img->pixels;
	uint img_w = img->width;
	uint img_h = img->height;
	uint img_sz = img_w * img_h * 3;
	uint cb_sz = width_ * height_;

	for (uint i = 0; i < img_sz; i += 3) {
		uchar b = pixels[i];
		uchar g = pixels[i + 1];
		uchar r = pixels[i + 2];
		uint ix = i / 3 % img_w;
		uint iy = i / 3 / img_w;
		uint bx = ix + start_x;
		uint by = iy + start_y;
		uint b_index = by * width_ + bx;
		if (b_index >= cb_sz) {
			continue;
		}
		buffer_[b_index] = color(r, g, b, 255);
	}
}

void color_buffer::_write_BGR_2_colorbuffer(image_data *img, uint start_x, uint start_y) {
	uchar *pixels = img->pixels;
	uint img_w = img->width;
	uint img_h = img->height;
	uint img_sz = img_w * img_h * 3;
	uint cb_sz = width_ * height_;

	for (uint i = 0; i < img_sz; i += 3) {
		uchar b = pixels[i];
		uchar g = pixels[i + 1];
		uchar r = pixels[i + 2];
		uint ix = i / 3 % img_w;
		uint iy = i / 3 / img_w;
		uint bx = ix + start_x;
		uint by = iy + start_y;
		uint b_index = by * width_ + bx;
		if (b_index >= cb_sz) {
			continue;
		}
		buffer_[b_index] = color(r, g, b, 255);
	}
}

HEL_API void color_buffer::write_pixels(image_data *img, uint start_x, uint start_y) {
	switch (img->format) {
	case IMG_FORMAT_NULL:
		log_print("img format error...");
		break;
	case IMG_FORMAT_RGBA:
		_write_RGBA_2_colorbuffer(img, start_x, start_y);
		break;
	case IMG_FORMAT_BGRA:
		_write_BGRA_2_colorbuffer(img, start_x, start_y);
		break;
	case IMG_FORMAT_RGB:
		_write_RGB_2_colorbuffer(img, start_x, start_y);
		break;
	case IMG_FORMAT_BGR:
		_write_BGR_2_colorbuffer(img, start_x, start_y);
		break;
	default:
		break;
	}
}

HEL_API void color_buffer::read_color(uint x, uint y, color *c) {
	uint i = y * width_ + x;
	color _c = buffer_[i];
	c->r = _c.r;
	c->g = _c.g;
	c->b = _c.b;
	c->a = _c.a;
}

HEL_API void color_buffer::set_clear_color(color c) {
	glClearColor(c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a / 255.0f);
}

HEL_API void color_buffer::clear(color c) {
	//TODO need improve performance.
	uint sz = width_ * height_;
	for (uint i = 0; i < sz; i++) {
		buffer_[i] = c;
	}
}

HEL_API void color_buffer::flush() {
	_gen_pixels();
	glDrawPixels(width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, pixels_);
}

void color_buffer::_gen_pixels() {
	if (pixels_ == nullptr) {
		pixels_ = new uchar[width_ * height_ * 4];
	}
	uint idx = 0;
	for (int row = height_ - 1; row >= 0; row--) {
		for (int col = 0; col < width_; col++) {
			uint i = row * width_ + col;
			color c = buffer_[i];
			pixels_[idx * 4] = c.r & 0xff;
			pixels_[idx * 4 + 1] = c.g & 0xff;
			pixels_[idx * 4 + 2] = c.b & 0xff;
			pixels_[idx * 4 + 3] = c.a & 0xff;
			++idx;
		}
	}
}

HEL_API color_buffer * device_create_colorbuffer(uint width, uint height) {
	color_buffer *cb = new color_buffer(width, height);
	return cb;
}

HEL_API void device_release_colorbuffer(color_buffer *cb) {
	delete cb;
}