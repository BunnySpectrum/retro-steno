#ifndef _RS_STDIO_H_
#define _RS_STDIO_H_

#include <stdio.h>
#include <stdarg.h>

#include "utils/rs_codes.h"
#include "utils/rs_stdint.h"

typedef struct Logger{
    int (*printer)(struct Logger logger, const char* fmt, va_list args);
    void* options;
}Logger_s;


void rs_log(Logger_s logger, const char* fmt, ...);

int rs_vprintf(Logger_s logger, const char* fmt, va_list args);

RS_CODE_e rs_getchar_timeout_us(uint32_t timeout, int *val);

#endif