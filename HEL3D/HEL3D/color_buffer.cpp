#include "device.h"

#include <assert.h>
#include <memory.h>

#include "common_header.h"

const int CB_MAX_W = 3000;
const int CB_MAX_H = 3000;

color_buffer::color_buffer(uint width, uint height) 
:width_(width), height_(height)
{
	assert(width_ > 0 && width_ < CB_MAX_W);
	assert(height_ > 0 && height_ < CB_MAX_H);
	buffer_ = new color[width_ * height_];
}

color_buffer::~color_buffer() {
	delete buffer_;
}

void color_buffer::write_color(uint x, uint y, color c) {
	uint i = y * width_ + x;
	buffer_[i] = c;
}

void color_buffer::read_color(uint x, uint y, color *c) {
	uint i = y * width_ + x;
	color _c = buffer_[i];
	c->r = _c.r;
	c->g = _c.g;
	c->b = _c.b;
	c->a = _c.a;
}

void color_buffer::clear() {
	memset(buffer_, 0, width_ * height_ * sizeof(color));
}

void color_buffer::flush() {
	//TODO
}

HEL_API color_buffer * device_create_colorbuffer(uint width, uint height) {
	color_buffer *cb = new color_buffer(width, height);
	return cb;
}

HEL_API void device_release_colorbuffer(color_buffer *cb) {
	delete cb;
}