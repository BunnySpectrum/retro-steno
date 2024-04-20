#include "rs_stdio.h"

void rs_log(Logger_s logger, const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    (*logger.printer)(logger, fmt, args);
    va_end(args);
}

int rs_vprintf(Logger_s logger, const char* fmt, va_list args){
    return vprintf(fmt, args);
}