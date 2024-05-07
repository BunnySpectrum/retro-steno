#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#include "utils/rs_stdint.h"
#include "utils/rs_codes.h"

uint64_t get_tick();
void rs_sleep_ms(uint32_t value);
RS_CODE_e sys_time_init(uint64_t val);

#endif
