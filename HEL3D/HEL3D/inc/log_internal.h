#ifndef log_internal_h
#define log_internal_h

#include <string>
#include <list>

enum arg_type {
	AT_NULL = 0,
	AT_INT,
	AT_FLOAT,
	AT_STRING
};

class arg {
public:
	arg();
	arg(int);
	arg(float);
	arg(std::string);
	arg(const char *s);
	~arg();
public:
	int v_int_;
	float v_float_;
	std::string v_string_;
	enum arg_type type();
private:
	enum arg_type at_;
};

class arg_list {
public:
	arg_list();
	arg_list(arg a1);
	arg_list(arg a1, arg a2);
	arg_list(arg a1, arg a2, arg a3);
	arg_list(arg a1, arg a2, arg a3, arg a4);
	arg_list(arg a1, arg a2, arg a3, arg a4, arg a5);
	~arg_list();
public:
	arg pop();
private:
	std::list<arg> args_;
};

void log_print(const char *format);
void log_print(std::string format);
void log_print(const char *format, arg_list alist);
void log_print(std::string format, arg_list alist);

#endif