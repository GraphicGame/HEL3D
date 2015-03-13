#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "GL/glew.h"
#include "device.h"
#include "framework.h"
#include "common_header.h"

#define WINDOW_CLASS_NAME "WIN_LAUNCHER"

typedef void(*FUNC)();
static FUNC on_draw;

static HWND s_Hwnd = NULL;
static uint s_FPS = 30;

static uint s_WindowWidth = 100;
static uint s_WindowHeight = 100;

static void set_pixel_format(HDC hdc) {
	PIXELFORMATDESCRIPTOR pfd;

	int color_deep = GetDeviceCaps(hdc, BITSPIXEL);
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = color_deep;
	pfd.cDepthBits = 0;
	pfd.cStencilBits = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);
}

static void init_ogl(HWND hwnd) {
	HDC hdc = GetDC(hwnd);
	set_pixel_format(hdc);
	HGLRC glrc = wglCreateContext(hdc);
	if (glrc == 0) {
		exit(1);
	}
	wglMakeCurrent(hdc, glrc);

	if (glewInit() != GLEW_OK) {
		exit(1);
	}
	glViewport(0, 0, s_WindowWidth, s_WindowHeight);

	ReleaseDC(hwnd, hdc);
}

LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
    case WM_CREATE:
		init_ogl(hwnd);
		SetTimer(hwnd, 0, s_FPS, NULL);
		break;
	case WM_TIMER:
		if (on_draw) {
			on_draw();
		}
		InvalidateRect(hwnd, NULL, false);
		break;
    case WM_PAINT:
		if (GetUpdateRect(hwnd, NULL, false)) {
			HDC hdc = GetDC(hwnd);
			SwapBuffers(hdc);
			ValidateRect(hwnd, NULL);
			ReleaseDC(hwnd, hdc);
		}
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }
	
    return (DefWindowProc(hwnd, msg, wparam, lparam));
}

static void init_console() {
	AllocConsole();
	FILE *new_file;
	freopen_s(&new_file, "CONIN$", "r", stdin);
	freopen_s(&new_file, "CONOUT$", "w", stdout);
	freopen_s(&new_file, "CONOUT$", "w", stderr);
}

HEL_API bool device_create_window(uint width, uint height) {
	assert(width > 0 && width < 3000);
	assert(width > 0 && width < 3000);
	s_WindowWidth = width;
	s_WindowHeight = height;

	init_console();

	WNDCLASSEX winclass;
	HWND hwnd;
	MSG msg;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = window_proc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = GetModuleHandleW(0);
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass))
		return false;

	hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		"HEL Soft Rasterizer",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100,
		width, height,
		NULL,
		NULL,
		GetModuleHandleW(0),
		NULL);
	if (hwnd == NULL)
		return false;

	s_Hwnd = hwnd;
	return true;
}

HEL_API void device_main_loop() {
	MSG msg;
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	device_create_window(960, 640);
	device_main_loop();
	return 0;
}

HEL_API void device_set_fps(uint fps) {
	s_FPS = fps;
	if (s_Hwnd) {
		SetTimer(s_Hwnd, 0, s_FPS, NULL);
	}
}

HEL_API void device_register_draw_func(FUNC draw_func) {
	on_draw = draw_func;
}

HEL_API void device_log(const char *msg) {
	printf(msg);
	printf("\n");
}