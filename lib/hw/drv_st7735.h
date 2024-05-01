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

#include "st7735.h"
#include "st7735_reg.h"

#define MAX_NUM_DISPLAY_DRIVERS 2

typedef struct DISP_CTX_ST7735{
    uint32_t objID;
    uint32_t dispCSPin;
    uint32_t dispDCPin;
    uint32_t cardCSPin;
    uint32_t resetPin;
    uint32_t lightPin;
    uint32_t colorCoding;
    uint32_t orientation;
    uint8_t spiID;
    ST7735_Object_t *pDriver;
}DISP_CTX_ST7735_s;


RS_CODE_e rs_st7735_init(DISP_CTX_ST7735_s *pCtx);
RS_CODE_e rs_st7735_draw_pixel(uint8_t driverID, uint32_t x, uint32_t y, RS_RGB565_e color);
RS_CODE_e rs_st7735_draw_rect(uint8_t driverID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e color);
// RS_CODE_e rs_st7735_draw_rect_bit(uint8_t driverID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e* colors);




#endif