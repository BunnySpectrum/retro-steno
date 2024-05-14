#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "utils/rs_stdint.h"
#include <stdlib.h>
#include "utils/rs_colors.h"
#include "bsp/display.h"
#include "app/gfx/gfx_core.h"
#include "app/model_point.h"
#include "bsp/keyboard.h"

// simple periodic task to toggle LED

#define SCREEN_TASK_PERIOD_MS 500

void screen_init(uint8_t count);
void screen_update();
void display_keyboard_callback(mpBase_t *mp, mpSubscriber_t *sub);

#endif
