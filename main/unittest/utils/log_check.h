#ifndef _LOG_CHECK_H_
#define _LOG_CHECK_H_

#include "utils/rs_stdio.h"

int mock_vprintf(Logger_s logger, const char* fmt, va_list args);

#endif