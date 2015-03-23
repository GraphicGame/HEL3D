#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "device.h"
#include "image.h"
#include "render_object.h"

const int WW = 960;
const int WH = 640;

color ClearColor = {0, 0, 0, 255};
color_buffer *CB = nullptr;
image_data *img_data = nullptr;
render_object *RO = nullptr;

static void on_draw() {
	CB->clear(ClearColor);

	CB->write_pixels(img_data, 0, 0);

	for (uint row = 0; row < 100; row++) {
		for (uint col = 0; col < 100; col++) {
			if (row <= 50)
				CB->write_color(col, row, color(255, 0, 0, 255));
			else
				CB->write_color(col, row, color(0, 0, 255, 255));
		}
	}

	for (int i = 0; i < 2000; i++) {
		device_draw_line(CB, rand() % 960, rand() % 640, rand() % 960, rand() % 640, color(rand() % 255, rand() % 255, rand() % 255, 255));
	}

	CB->flush();
}

static void load_img(const char *path) {
	if (img_data == nullptr) {
		img_data = new image_data();
	}
	img_decode_image(path, img_data);
}

int main(int argc, char *argv[]) {
	CB = device_create_colorbuffer(WW, WH);
	device_create_window(WW + 30, WH + 30);

	load_img("E:/test.jpg");

	RO = render_create_object();
	RO->load_model("E://simple_model.txt");

	device_register_draw_func(on_draw);
	device_main_loop();

	getchar();
	return 0;
}