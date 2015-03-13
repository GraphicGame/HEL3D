#include <stdio.h>
#include <stdlib.h>

#include "device.h" 

const int WW = 960;
const int WH = 640;

color ClearColor = {0, 0, 0, 0};
color_buffer *CB = NULL;

static void on_draw() {
	CB->clear(ClearColor);
	for (uint row = 0; row < 100; row++) {
		for (uint col = 0; col < 100; col++) {
			CB->write_color(col, row, color(255, 255, 0, 255));
		}
	}
	CB->flush();
}

int main(int argc, char *argv[]) {
	CB = device_create_colorbuffer(WW, WH);
	device_create_window(WW, WH);
	device_register_draw_func(on_draw);
	device_main_loop();

	getchar();
	return 0;
}