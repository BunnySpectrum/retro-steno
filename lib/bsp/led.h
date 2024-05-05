#ifndef _LED_H_
#define _LED_H_

#include "utils/rs_stdint.h"
#include "utils/sys_time.h"
#include "bsp/pinmap.h"
#include "hw/drv_gpio.h"


void blink(uint8_t count, uint16_t delay);

#endif
