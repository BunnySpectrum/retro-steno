#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "bsp/display_objs.h"
#include "bsp/devices/displays/display_manifest.h"

#include "st7735_reg.h"
#include "st7735.h"

#include "utils/rs_stdio.h"
#include "hw/drv_spi.h"
#include "hw/drv_st7735.h"
#include "hw/drv_ssd1306.h"
#include "hw/drv_gpio.h"
#include "bsp/pinmap.h"

#include "utils/sys_time.h"

#define DISP_ORIGIN_X 2
#define DISP_ORIGIN_Y 3

#define MAX_NUM_DISPLAYS 2

typedef struct DISP_CTX{
    DisplayName_e name;
    uint32_t objID;
    void* driverCtx;
}DISP_CTX_s;
// Note, may change to have a driverCtx be fptrs, and change what is currently driverCtx to be hardwareCtx



void display_init();
void add_displays(DISP_CTX_s *ctxList[], uint32_t length);
void add_display(DISP_CTX_s *pCtx);
void set_logger_display(Logger_s printer);
void display_reset();
RS_CODE_e display_draw_pixel(uint32_t displayID, uint32_t x, uint32_t y, RS_RGB565_e color);
RS_CODE_e display_draw_rect(uint32_t displayID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e color);
RS_CODE_e display_draw_rect_bit(uint32_t displayID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e* pColors);

RS_CODE_e get_metrics_for_display(uint32_t displayID, const DisplayMetrics_s **metrics);

#endif