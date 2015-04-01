#ifndef device_h_
#define device_h_

#include "common_header.h"
#include "image.h"

#ifdef __cplusplus
extern "C" {
#endif
	
class color {
public:
	uint r, g, b, a;
	color();
	color(uint _r, uint _g, uint _b, uint _a);

	void modulate(float s);
	void add(const color &c);
};

class color_buffer {
public:
	color_buffer(uint width, uint height);
	~color_buffer();
public:
	HEL_API void write_color(uint x, uint y, color c);
	HEL_API void write_pixels(image_data *img, uint start_x, uint start_y);
	HEL_API void read_color(uint x, uint y, color *c);
	HEL_API void set_clear_color(color c);
	HEL_API void clear(color c);
	HEL_API void flush();
private:
	void _gen_pixels();
	bool dirty_; //TODO 

	void _write_RGBA_2_colorbuffer(image_data *img, uint start_x, uint start_y);
	void _write_BGRA_2_colorbuffer(image_data *img, uint start_x, uint start_y);
	void _write_RGB_2_colorbuffer(image_data *img, uint start_x, uint start_y);
	void _write_BGR_2_colorbuffer(image_data *img, uint start_x, uint start_y);

private:
	uint width_;
	uint height_;
	color *buffer_;
	uchar *pixels_;
};

HEL_API bool device_create_window(uint width, uint height);
HEL_API void device_main_loop();

HEL_API color_buffer * device_create_colorbuffer(uint width, uint height);
HEL_API void device_release_colorbuffer(color_buffer *cb);

HEL_API void device_set_fps(uint fps);
HEL_API void device_register_draw_func(void(*func)());

HEL_API void device_draw_line(color_buffer *cb, int x0, int y0, int x1, int y1, color c);

#ifdef __cplusplus
}
#endif

#endif