#ifndef device_h_
#define device_h_

#include "common_header.h"

#ifdef __cplusplus
extern "C" {
#endif
	
typedef struct color {
	float r, g, b, a;
} color;

typedef unsigned int uint;

class color_buffer {
public:
	color_buffer(uint width, uint height);
	~color_buffer();
public:
	void write_color(uint x, uint y, color c);
	void read_color(uint x, uint y, color *c);
	void clear();
	void flush();
private:
	uint width_;
	uint height_;
	color *buffer_;
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