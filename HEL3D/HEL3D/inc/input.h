#ifndef input_h
#define input_h

#include "common_header.h"

enum mouse_state {
	LBUTTON_DOWN = 0,
	LBUTTON_UP,
	LBUTTON_CLICK,
};

enum keyboard_state {
	KEY_DOWN = 0,
	KEY_UP,
	KEY_LAST
};

typedef void(*MOUSE_FUNC)(enum mouse_state state, int x, int y);
typedef void(*KEYBOARD_FUNC)(enum keyboard_state state, int code);

HEL_API void input_register_mouse_func(MOUSE_FUNC func);
HEL_API void input_register_keyboard_func(KEYBOARD_FUNC func);

#endif