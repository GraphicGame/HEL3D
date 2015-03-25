#ifndef utils_h
#define utils_h

#include "common_header.h"

HEL_API wchar_t* char2wchar_t(const char *str);
HEL_API char* wchar_t2char(const wchar_t *str);

HEL_API float deg_2_rad(float deg);
HEL_API float rad_2_deg(float rad);

#endif