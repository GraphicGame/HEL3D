#define __exec

#include <stdio.h>
//#include <Winuser.h>

#include "device.h"
#include "input.h"

static const int WW = 960;
static const int WH = 640;

static color_buffer *CB = nullptr;
static color ClearColor(0, 0, 0, 255);
static float S = 1.0f;
static const float S_STEP = 0.06f;
static bool Auto_S = false;

static enum auto_state {
	S_UP = 0,
	S_DOWN = 1
};
static auto_state State = S_DOWN;

static void on_draw() {
	CB->clear(ClearColor);
	
	color c(0, 0, 255, 255);
	c.modulate(S);

	if (Auto_S) {
		if (State == S_DOWN) {
			S -= S_STEP;
			if (S < 0) {
				S = 0.0f;
				State = S_UP;
			}
		}
		else if (State == S_UP) {
			S += S_STEP;
			if (S > 1) {
				S = 1.0f;
				State = S_DOWN;
			}
		}
	}

	for (int i = 100; i < 200; i++) {
		for (int j = 100; j < 200; j++) {
			CB->write_color(j, i, c);
		}
	}

	CB->flush();
}

static void on_key(keyboard_state ks, int code) {
	switch (code) {
	case 0x26: //up
		Auto_S = false;
		S += S_STEP;
		if (S > 1.0f) {
			S = 1.0f;
		}
		break;
	case 0x28: //down
		Auto_S = false;
		S -= S_STEP;
		if (S < 0.0f) {
			S = 0.0f;
		}
		break;
	case 0x0D:
		if (ks == KEY_UP)
			Auto_S = !Auto_S;
		break;
	default:
		break;
	}
}

#ifdef __exec
int main(int argc, char *argv[]) {
	CB = device_create_colorbuffer(WW, WH);
	device_create_window(WW, WH);

	device_register_draw_func(on_draw);
	input_register_keyboard_func(on_key);
	device_main_loop();

	getchar();
	return 0;
}
#endif