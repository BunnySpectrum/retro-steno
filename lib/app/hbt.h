#ifndef _HBT_H_
#define _HBT_H_

#include "bsp/pinmap.h"
#include "hw/drv_gpio.h"

// simple periodic task to toggle LED

#define HBT_TASK_PERIOD_MS 500

void hbt_init();
void hbt_toggle();

#endif
