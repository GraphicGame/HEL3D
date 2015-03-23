#ifndef framework_h
#define framework_h

typedef void(*FW_FUNC)();
typedef struct framework {
	FW_FUNC on_start;
	FW_FUNC on_update;
} framework;

#endif