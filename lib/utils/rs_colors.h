#ifndef _RS_COLORS_H_
#define _RS_COLORS_H_

#include "utils/rs_stdint.h"
#include "utils/rs_codes.h"

#define RGB565_COLOR_COUNT 8
#define RGB888_COLOR_COUNT 8

// https://chrishewett.com/blog/true-rgb565-colour-picker/
typedef enum RS_RGB565{
    RS_RGB565_BLACK = 0x0000,
    RS_RGB565_WHITE = 0xFFFF,
    RS_RGB565_RED = 0xF800,
    RS_RGB565_YELLOW = 0xFFE0,
    RS_RGB565_MAGENTA = 0xF81F,
    RS_RGB565_GREEN = 0x07E0,
    RS_RGB565_CYAN = 0x07FF,
    RS_RGB565_BLUE = 0x001F,

}RS_RGB565_e;

static const RS_RGB565_e rgb565List[RGB565_COLOR_COUNT] = {
    RS_RGB565_BLACK, 
    RS_RGB565_RED, 
    RS_RGB565_GREEN, 
    RS_RGB565_YELLOW,
    RS_RGB565_BLUE,
    RS_RGB565_MAGENTA,
    RS_RGB565_CYAN,
    RS_RGB565_WHITE
};

typedef enum RS_RGB888{
    RS_RGB888_BLACK = 0x000000,
    RS_RGB888_WHITE = 0xFFFFFF,
    RS_RGB888_RED = 0xFF0000,
    RS_RGB888_YELLOW = 0xFFFF00,
    RS_RGB888_MAGENTA = 0xFF00FF,
    RS_RGB888_GREEN = 0x00FF00,
    RS_RGB888_CYAN = 0x00FFFF,
    RS_RGB888_BLUE = 0x0000FF,

}RS_RGB888_e;

RS_CODE_e rgb565_for_index(uint8_t idx, RS_RGB565_e *color);

#endif