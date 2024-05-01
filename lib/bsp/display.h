#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "st7735_reg.h"
#include "st7735.h"

#include "utils/rs_stdio.h"
#include "hw/drv_spi.h"
#include "hw/drv_st7735.h"
#include "hw/drv_gpio.h"
#include "bsp/pinmap.h"

#include "pico/time.h"

#define DISP_ORIGIN_X 2
#define DISP_ORIGIN_Y 3

typedef struct DISP_CTX{
    uint32_t objID;
    void* driverCtx;
}DISP_CTX_s;

void display_init(DISP_CTX_s *ctxList, uint32_t length);
void set_logger_display(Logger_s printer);
void display_reset();

#endif