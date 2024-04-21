#ifndef _LOG_CHECK_H_
#define _LOG_CHECK_H_

#include "utils/rs_stdio.h"

#define MAX_BUF_LEN 128

int mock_vprintf(Logger_s logger, const char* fmt, va_list args);
int mock_vsnprintf(Logger_s logger, const char* fmt, va_list args);

void start_log_buf(void);
void dump_buffer(void);

#endif