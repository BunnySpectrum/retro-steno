#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "utils/rs_stdint.h"
#include "utils/rs_colors.h"
#include "bsp/display.h"
#include "app/gfx/gfx_font.h"

// simple periodic task to toggle LED

#define SCREEN_TASK_PERIOD_MS 500

static RS_RGB565_e imageBuffer[32*32];

void screen_init(uint8_t count);
void screen_update();

#endif
