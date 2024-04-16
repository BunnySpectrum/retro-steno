#ifndef _RS_STDIO_H_
#define _RS_STDIO_H_

#include <stdio.h>
#include <stdarg.h>

typedef struct Logger{
    int (*printer)(struct Logger logger, const char* fmt, va_list args);
    void* options;
}Logger_s;


void rs_log(Logger_s logger, const char* fmt, ...);

int rs_vprintf(Logger_s logger, const char* fmt, va_list args);

#endif