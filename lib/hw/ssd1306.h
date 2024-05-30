
#ifndef _SSD1306_H_
#define _SSD1306_H_

#include "utils/rs_stdint.h"
#include "hw/ssd1306_reg.h"


typedef RC_SSD1306_e (*SSD1306_WriteCmd_Func)(void *, uint8_t*, uint32_t);

typedef struct
{
  SSD1306_WriteCmd_Func   WriteCmd;
  void                *handle;
} SSD1306_ctx_s;



typedef struct SSD1306_Object{
    SSD1306_ctx_s ctx;
    uint8_t isInitialized;
}SSD1306_Object_s;

// TODO need to move config info out of DISP_CTX_SSD1306 and into here


RC_SSD1306_e ssd1306_init(SSD1306_Object_s *pObj, uint32_t orientation, uint32_t height);
RC_SSD1306_e ssd1306_set_pixel(SSD1306_Object_s *pObj, uint32_t x, uint32_t y, uint32_t color);
RC_SSD1306_e ssd1306_fill_rect(SSD1306_Object_s *pObj, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);
RC_SSD1306_e ssd1306_bitmap_rect(SSD1306_Object_s *pObj, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t* pColors);
#endif