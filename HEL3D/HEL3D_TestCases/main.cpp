#include <stdio.h>

#include "device.h" 

int main(int argc, char *argv[]) {
	device_create_window(960, 640);
	device_main_loop();

	getchar();
	return 0;
}