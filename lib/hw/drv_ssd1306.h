
#ifndef _DRV_SSD1306_H_
#define _DRV_SSD1306_H_

#include "rs_stdint.h"
#include "rs_codes.h"
#include "hw/drv_i2c.h"
#include "hw/ssd1306.h"

#define MAX_NUM_SSD1306 2

typedef struct DISP_CTX_SSD1306{
    uint32_t objID;
    uint8_t i2cID;
    uint8_t i2cAddr;
    SSD1306_Object_s *pDriver;
}DISP_CTX_SSD1306_s;

RS_CODE_e rs_ssd1306_write_reg(void *pCtx, uint8_t reg, uint8_t *pData, uint32_t length);

#endif