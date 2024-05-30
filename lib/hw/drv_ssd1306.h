
#ifndef _DRV_SSD1306_H_
#define _DRV_SSD1306_H_

#include "utils/rs_stdint.h"
#include "utils/rs_codes.h"
#include "utils/rs_colors.h"
#include "hw/drv_i2c.h"
#include "hw/ssd1306.h"

#define MAX_NUM_SSD1306 3

typedef struct DISP_CTX_SSD1306{
    SSD1306_Object_s *pDriver;
    uint32_t objID;
    uint32_t orientation;
    uint8_t i2cID;
    uint8_t i2cAddr;
}DISP_CTX_SSD1306_s;

// Functions needed for SSD1306 driver
RC_SSD1306_e rs_ssd1306_write_cmd(void *pCtx, uint8_t *pData, uint32_t length);

// Functions needed for rest of RS application
RS_CODE_e rs_ssd1306_init(DISP_CTX_SSD1306_s *pCtx);
RS_CODE_e rs_ssd1306_reset(DISP_CTX_SSD1306_s *pCtx);
RS_CODE_e rs_ssd1306_draw_pixel(uint8_t driverID, uint32_t x, uint32_t y, RS_RGB565_e color);
RS_CODE_e rs_ssd1306_draw_rect(uint8_t driverID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e color);
RS_CODE_e rs_ssd1306_draw_rect_bit(uint8_t driverID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e* pColors);





#endif