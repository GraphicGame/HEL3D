//#define __exec

#include <stdio.h>
//#include <Winuser.h>

#include "device.h"
#include "input.h"

static const int WW = 960;
static const int WH = 640;

static color_buffer *s_cb = nullptr;
static color s_clearcolor(0, 0, 0, 255);
static float s_modulas = 1.0f;
static const float S_STEP = 0.06f;
static bool s_auto = false;

static enum auto_state {
	S_UP = 0,
	S_DOWN = 1
};
static auto_state State = S_DOWN;

static void on_draw() {
	s_cb->clear(s_clearcolor);
	
	color c(0, 0, 255, 255);
	c.modulate(s_modulas);

	if (s_auto) {
		if (State == S_DOWN) {
			s_modulas -= S_STEP;
			if (s_modulas < 0) {
				s_modulas = 0.0f;
				State = S_UP;
			}
		}
		else if (State == S_UP) {
			s_modulas += S_STEP;
			if (s_modulas > 1) {
				s_modulas = 1.0f;
				State = S_DOWN;
			}
		}
	}

	for (int i = 100; i < 200; i++) {
		for (int j = 100; j < 200; j++) {
			s_cb->write_color(j, i, c);
		}
	}

	s_cb->flush();
}

static void on_key(keyboard_state ks, int code) {
	switch (code) {
	case 0x26: //up
		s_auto = false;
		s_modulas += S_STEP;
		if (s_modulas > 1.0f) {
			s_modulas = 1.0f;
		}
		break;
	case 0x28: //down
		s_auto = false;
		s_modulas -= S_STEP;
		if (s_modulas < 0.0f) {
			s_modulas = 0.0f;
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

#ifdef __exec
int main(int argc, char *argv[]) {
	s_cb = device_create_colorbuffer(WW, WH);
	device_create_window(WW, WH);

	device_register_draw_func(on_draw);
	input_register_keyboard_func(on_key);
	device_main_loop();

	getchar();
	return 0;
}
#endif