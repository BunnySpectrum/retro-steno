#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "utils/rs_stdint.h"
#include "utils/rs_colors.h"
#include "bsp/display.h"

// simple periodic task to toggle LED

#define SCREEN_TASK_PERIOD_MS 500



void screen_init(uint8_t count);
void screen_update();

#endif
