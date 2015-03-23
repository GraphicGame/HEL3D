#include "device.h"

#include <math.h>

HEL_API void device_draw_line(color_buffer *cb, int x0, int y0, int x1, int y1, color c) {
	double dx = x1 - x0;
	double dy = y1 - y0;
	double m = dy / dx;
	double y = y0;
	for (int x = x0; x <= x1; x++) {
		cb->write_color(x, floor(y + 0.5f), c);
		y += m;
	}
}