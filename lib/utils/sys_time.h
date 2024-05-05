#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include "utils/rs_stdint.h"

uint32_t get_tick();
void rs_sleep_ms(uint32_t value);

#endif
