#include "log.h"
#include "log_internal.h"
#include <strstream>
using namespace std;

#include <assert.h>

static LOG_FUNC log_func = nullptr;

arg::arg() 
:at_(AT_NULL) {
}

arg::arg(int v)
: at_(AT_INT), v_int_(v) {
}

arg::arg(float v)
: at_(AT_FLOAT), v_float_(v) {
}

arg::arg(string v)
: at_(AT_STRING), v_string_(v) {
}

arg::arg(const char *s) 
: at_(AT_STRING), v_string_(s) {
}

arg::~arg() {
}

enum arg_type arg::type() {
	return at_;
}

arg_list::arg_list() {
}

arg_list::arg_list(arg a1) {
	args_.push_back(a1);
}

arg_list::arg_list(arg a1, arg a2) {
	args_.push_back(a1);
	args_.push_back(a2);
}

arg_list::arg_list(arg a1, arg a2, arg a3) {
	args_.push_back(a1);
	args_.push_back(a2);
	args_.push_back(a3);
}

arg_list::arg_list(arg a1, arg a2, arg a3, arg a4) {
	args_.push_back(a1);
	args_.push_back(a2);
	args_.push_back(a3);
	args_.push_back(a4);
}

arg_list::arg_list(arg a1, arg a2, arg a3, arg a4, arg a5) {
	args_.push_back(a1);
	args_.push_back(a2);
	args_.push_back(a3);
	args_.push_back(a4);
	args_.push_back(a5);
}

arg_list::~arg_list() {
}

arg arg_list::pop() {
	assert(args_.size() > 0);
	arg a = args_.front();
	args_.pop_front();
	return a;
}

HEL_API void log_register_logfunc(LOG_FUNC func) {
	log_func = func;
}

template <typename T>
static string _T2STR(T v) {
	strstream ss;
	string r;
	ss << v;
	ss >> r;
	return r;
}

void log_print(const char *format) {
	log_print(string(format));
}

void log_print(string format) {
	if (log_func) {
		log_func(format);
	}
}

void log_print(const char *format, arg_list alist) {
	log_print(string(format), alist);
}

void log_print(string format, arg_list alist) {
	string expand_str;
	int sz = format.size();
	for (int i = 0; i < sz; i++) {
		char c = format[i];
		if (c == '%') {
			char next_c = ' ';
			if (i < sz - 1)
				next_c = format[i + 1];
			if (next_c == 'd') {
				arg &ia = alist.pop();
				assert(ia.type() == AT_INT);
				expand_str += _T2STR(ia.v_int_);
				i++;
			}
			else if (next_c == 'f') {
				arg &ia = alist.pop();
				assert(ia.type() == AT_FLOAT);
				expand_str += _T2STR(ia.v_float_);
				i++;
			}
			else if (next_c == 's') {
				arg &ia = alist.pop();
				assert(ia.type() == AT_STRING);
				expand_str += ia.v_string_;
				i++;
			}
			else {
				expand_str += c;
			}
		}
		else {
			expand_str += c;
		}
	}

	if (log_func) {
		log_func(expand_str);
	}
}