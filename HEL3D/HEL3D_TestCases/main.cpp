#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

#include "device.h"
#include "image.h"
#include "render_object.h"
#include "camera.h"
#include "input.h"
#include "utils.h"

const int WW = 960;
const int WH = 640;

color ClearColor = {0, 0, 0, 255};
color_buffer *CB = nullptr;
image_data *img_data = nullptr;
render_object *RO = nullptr;
camera_euler *CAM = nullptr;

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

	for (int i = 0; i < 200; i++) {
		//device_draw_line(CB, rand() % 960, rand() % 640, rand() % 960, rand() % 640, color(rand() % 255, rand() % 255, rand() % 255, 255));
	}

	RO->draw(CAM, CB);

	CB->flush();
}

///for test...
static void on_mouse(enum mouse_state ms, int x, int y) {
	RO->load_model("E://simple_model.txt");
	CAM->__debug_load_config("E://camera_config.txt");
	cout << x << ":" << y << endl;
}

static void on_keyboard(enum keyboard_state ks, int code) {
	if (CAM == nullptr)
		return;

	float step = 0.06f;
	switch (code) {
	case 'W':
		CAM->pos().z += step;
		break;
	case 'A':
		CAM->pos().x -= step;
		break;
	case 'S':
		CAM->pos().z -= step;
		break;
	case 'D':
		CAM->pos().x += step;
		break;
	case 'Q':
		CAM->pos().y += step;
		break;
	case 'E':
		CAM->pos().y -= step;
		break;
	default:
		break;
	}
}

static void load_img(const char *path) {
	if (img_data == nullptr) {
		img_data = new image_data();
	}
	img_decode_image(path, img_data);
}

static void setup_render_stuff() {
	RO = render_create_object();
	RO->load_model("E://simple_model.txt");
	RO->world_pos_.x = 0; //1.6 2X2
	RO->world_pos_.y = 0; //
	RO->world_pos_.z = 2; //

	CAM = render_create_camera_euler();
	CAM->setup_camera(
		point4d(0, 0, 0, 1),
		vec4(0, 0, 0, 1),
		0, 100, 90, 960, 640
		);
	CAM->__debug_load_config("E://camera_config.txt");
	CAM->set_target(RO);

	//test and need be deleted.
	float x = -1;
	float y = -1;
	float angle_x = rad_2_deg(asin(y / sqrtf(x * x + y * y)));
	cout << "x=" << x << ",y=" << y << ", angle_x=" << angle_x;
	//end test.
}

int main(int argc, char *argv[]) {
	CB = device_create_colorbuffer(WW, WH);
	device_create_window(WW + 30, WH + 30);

	load_img("E:/test3.jpg");

	setup_render_stuff();
	
	device_register_draw_func(on_draw);
	input_register_mouse_func(on_mouse);
	input_register_keyboard_func(on_keyboard);
	device_main_loop();

	getchar();
	return 0;
}