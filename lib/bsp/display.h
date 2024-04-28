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

void display_init(uint8_t spiID, uint8_t driverID);
void set_logger_display(Logger_s printer);
void display_reset();

#endif