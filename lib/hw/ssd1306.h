
#ifndef _SSD1306_H_
#define _SSD1306_H_

#include "utils/rs_stdint.h"
#include "hw/ssd1306_reg.h"

typedef struct SSD1305_io{
    ;
}SSD1306_io_s;


typedef struct SSD1306_Object{
    SSD1306_io_s io;
    SSD1306_ctx_s ctx;
    uint8_t isInitialized;
}SSD1306_Object_s;

#endif