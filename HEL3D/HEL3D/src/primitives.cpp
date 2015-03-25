#include "device.h"

#include <math.h>

static inline void _swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

HEL_API void device_draw_line(color_buffer *cb, int x0, int y0, int x1, int y1, color c) {
	if (x0 > x1) {
		_swap(&x0, &x1);
		_swap(&y0, &y1);
	}
	/*if (y0 > y1) {
		_swap(&y0, &y1);
	}*/
	
	if (x0 == x1) {
		for (int y = y0; y <= y1; y++) {
			cb->write_color(x0, y, c);
		}
		return;
	}

	double dx = x1 - x0;
	double dy = y1 - y0;
	double m = dy / dx;
	double y = y0;
	for (int x = x0; x <= x1; x++) {
		cb->write_color(x, floor(y + 0.5f), c);
		y += m;
	}
}