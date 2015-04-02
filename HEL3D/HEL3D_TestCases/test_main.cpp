//#define __exec

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <iostream>
#include <string>
using namespace std;

#include "device.h"
#include "image.h"
#include "render_object.h"
#include "camera.h"
#include "input.h"
#include "utils.h"
#include "log.h"

static const int WW = 960;
static const int WH = 640;

static color s_clearcolor = {0, 0, 0, 255};
static color_buffer *s_cb = nullptr;
static image_data *s_img_data = nullptr;
static render_object *s_ro = nullptr;
static camera_euler *s_cam = nullptr;

static void on_draw() {
	s_cb->clear(s_clearcolor);

	s_cb->write_pixels(s_img_data, 0, 0);

	for (uint row = 0; row < 100; row++) {
		for (uint col = 0; col < 100; col++) {
			if (row <= 50)
				s_cb->write_color(col, row, color(255, 0, 0, 255));
			else
				s_cb->write_color(col, row, color(0, 0, 255, 255));
		}
	}

	for (int i = 0; i < 200; i++) {
		//device_draw_line(CB, rand() % 960, rand() % 640, rand() % 960, rand() % 640, color(rand() % 255, rand() % 255, rand() % 255, 255));
	}

	s_ro->draw(s_cam, s_cb);

	s_cb->flush();
}

///for test...
static void on_mouse(enum mouse_state ms, int x, int y) {
	s_ro->load_model("E://simple_model.txt");
	s_cam->__debug_load_config("E://camera_config.txt");
}

static void on_keyboard(enum keyboard_state ks, int code) {
	if (s_cam == nullptr)
		return;

	float step = 0.06f;
	switch (code) {
	case 'W':
		s_cam->pos().z += step;
		break;
	case 'A':
		s_cam->pos().x -= step;
		break;
	case 'S':
		s_cam->pos().z -= step;
		break;
	case 'D':
		s_cam->pos().x += step;
		break;
	case 'Q':
		s_cam->pos().y += step;
		break;
	case 'E':
		s_cam->pos().y -= step;
		break;
	default:
		break;
	}
}

static void log_console(string log) {
	cout << log << endl;
}

static void load_img(const char *path) {
	if (s_img_data == nullptr) {
		s_img_data = new image_data();
	}
	img_load_image(path, s_img_data);
}

static void setup_render_stuff() {
	s_ro = render_create_object();
	s_ro->load_model("E://simple_model.txt");
	s_ro->world_pos_.x = 0; //1.6 2X2
	s_ro->world_pos_.y = 0; //
	s_ro->world_pos_.z = 2; //

	s_cam = render_create_camera_euler();
	s_cam->setup_camera(
		point4d(0, 0, 0, 1),
		vec4(0, 0, 0, 1),
		0, 100, 90, 960, 640
		);
	s_cam->__debug_load_config("E://camera_config.txt");
	s_cam->set_target(s_ro);
}

#ifdef __exec
int main(int argc, char *argv[]) {
	log_register_logfunc(log_console);

	s_cb = device_create_colorbuffer(WW, WH);
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
#endif