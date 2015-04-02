#define __exec

#include <stdio.h>
#include "device.h"
#include "input.h"
#include "image.h"

static const int WW = 960;
static const int WH = 640;

static color_buffer *s_cb = nullptr;
static color s_clearcolor(0, 0, 0, 255);

static image_data *s_img1 = nullptr;
static image_data *s_img2 = nullptr;

static int s_alpha = 255;
static const int ALPHA_STEP = 10;
static bool s_auto = false;

enum auto_state {
	S_UP = 0,
	S_DOWN = 1
};
auto_state s_state = S_DOWN;

static void on_draw() {
	s_cb->clear(s_clearcolor);

	s_cb->write_pixels(s_img1, 100, 100, 255);

	s_cb->write_pixels(s_img2, 100, 100, s_alpha);

	if (s_auto) {
		if (s_state == S_DOWN) {
			s_alpha -= ALPHA_STEP;
			if (s_alpha < 0) {
				s_state = S_UP;
				s_alpha = 0;
			}
		}
		else if (s_state == S_UP) {
			s_alpha += ALPHA_STEP;
			if (s_alpha > 255) {
				s_state = S_DOWN;
				s_alpha = 255;
			}
		}
	}

	s_cb->flush();
}

static void on_key(keyboard_state ks, int code) {
	switch (code) {
	case 0x26: //up
		s_auto = false;
		s_alpha += ALPHA_STEP;
		if (s_alpha > 255) {
			s_alpha = 255;
		}
		break;
	case 0x28: //down
		s_auto = false;
		s_alpha -= ALPHA_STEP;
		if (s_alpha < 10) {
			s_alpha = 0;
		}
		break;
	case 0x0D:
		if (ks == KEY_UP)
			s_auto = !s_auto;
		break;
	default:
		break;
	}
}

static void load_images() {
	if (s_img1 == nullptr) {
		s_img1 = new image_data();
	}
	img_load_image("E://test3.jpg", s_img1);

	if (s_img2 == nullptr) {
		s_img2 = new image_data();
	}
	img_load_image("E://test2.jpg", s_img2);
}

#ifdef __exec
int main(int argc, char *argv[]) {
	s_cb = device_create_colorbuffer(WW, WH);
	device_create_window(WW + 30, WH + 30);

	load_images();

	device_register_draw_func(on_draw);
	input_register_keyboard_func(on_key);
	device_main_loop();

	getchar();
	return 0;
}
#endif