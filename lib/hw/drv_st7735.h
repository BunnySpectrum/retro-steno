#ifndef _DRV_ST7735_H_
#define _DRV_ST7735_H_

#include "utils/rs_stdint.h"
#include "utils/rs_stddef.h"
#include "utils/rs_stdio.h"
#include "utils/rs_codes.h"
#include "utils/rs_colors.h"

#include "bsp/pinmap.h"
#include "hw/drv_spi.h"
#include "hw/drv_gpio.h"
#include "pico/time.h"

#define MAX_NUM_DISPLAY_DRIVERS 2


RS_CODE_e rs_st7735_init(uint8_t spiID, uint8_t driverID);
RS_CODE_e rs_st7735_set_pixel(uint8_t driverID, uint32_t x, uint32_t y, RS_RGB565_e color);
RS_CODE_e rs_st7735_fill_rect(uint8_t driverID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e color);




#endif