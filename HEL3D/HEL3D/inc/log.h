#ifndef log_h
#define log_h

#include <string>

#include "common_header.h"

typedef void(*LOG_FUNC)(std::string log);

HEL_API void log_register_logfunc(LOG_FUNC func);

#endif