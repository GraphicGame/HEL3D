#ifndef device_h_
#define device_h_

#include "common_header.h"

#ifdef __cplusplus
extern "C" {
#endif
	
typedef class color {
public:
	uint r, g, b, a;
	color() {}
	color(uint _r, uint _g, uint _b, uint _a)
		:r(_r), g(_g), b(_b), a(_a)
	{	
	}
} color;

class color_buffer {
public:
	color_buffer(uint width, uint height);
	~color_buffer();
public:
	HEL_API void write_color(uint x, uint y, color c);
	HEL_API void read_color(uint x, uint y, color *c);
	HEL_API void set_clear_color(color c);
	HEL_API void clear(color c);
	HEL_API void flush();
private:
	void gen_pixels();
	bool dirty_; //TODO 
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

HEL_API void device_log(const char *msg);

#ifdef __cplusplus
}
#endif

#endif