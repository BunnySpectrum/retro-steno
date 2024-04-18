
#include "log_check.h"

int mock_vprintf(Logger_s logger, const char* fmt, va_list args){
    vprintf(fmt, args);
}