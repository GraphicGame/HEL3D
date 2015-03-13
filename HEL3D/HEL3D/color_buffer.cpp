#include "device.h"

#include <assert.h>
#include <memory.h>

#include "common_header.h"
#include "GL/glew.h"

const int CB_MAX_W = 3000;
const int CB_MAX_H = 3000;

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
	uint i = y * width_ + x;
	buffer_[i] = c;
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
	memset(buffer_, 0, width_ * height_ * sizeof(color));
	glClearColor(c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

HEL_API void color_buffer::flush() {
	gen_pixels();
	glDrawPixels(width_, height_, GL_RGBA, GL_UNSIGNED_BYTE, pixels_);
}

void color_buffer::gen_pixels() {
	if (pixels_ == nullptr) {
		pixels_ = new uchar[width_ * height_ * 4];
	}
	uint sz = width_ * height_;
	for (int i = 0; i < sz; i++) {
		color c = buffer_[i];
		pixels_[i * 4] = (c.r) & 0xff;
		pixels_[i * 4 + 1] = (c.g) & 0xff;
		pixels_[i * 4 + 2] = (c.b) & 0xff;
		pixels_[i * 4 + 3] = (c.a) & 0xff;
	}
}

HEL_API color_buffer * device_create_colorbuffer(uint width, uint height) {
	color_buffer *cb = new color_buffer(width, height);
	return cb;
}

HEL_API void device_release_colorbuffer(color_buffer *cb) {
	delete cb;
}