
#ifndef _DRV_SSD1306_REG_H_
#define _DRV_SSD1306_REG_H_

#include "utils/rs_codes.h"
#include "utils/rs_stdint.h"

typedef enum CMD_SSD1306{
    // Command table 9-1
    CMD_SSD1306_SET_CONTRAST_CONTROL = 0x81,
    CMD_SSD1306_ON_FOLLOW_RAM = 0xA4,
    CMD_SSD1306_ON_IGNORE_RAM = 0xA5,
    CMD_SSD1306_NORMAL_DISPLAY = 0xA6,
    CMD_SSD1306_INVERSE_DISPLAY = 0xA7,
    CMD_SSD1306_DISPLAY_ON = 0xAF,
    CMD_SSD1306_DISPLAY_OFF = 0xAE,

    // Scrolling command table
    CMD_SSD1306_RIGHT_HSCROLL_SETUP = 0x26,
    CMD_SSD1306_LEFT_HSCROLL_SETUP = 0x27,
    CMD_SSD1306_V_RIGHT_HSCROLL_SETUP = 0x29,
    CMD_SSD1306_V_LEFT_HSCROLL_SETUP = 0x2A,
    CMD_SSD1306_DEACTIVATE_SCROLL = 0x2E,
    CMD_SSD1306_ACTIVATE_SCROLL = 0x2F,
    CMD_SSD1306_VSCROLL_AREA = 0xA3,

    // Address setting command table
    CMD_SSD1306_LOWWER_COL_PAGE_START = 0x00,
    CMD_SSD1306_UPPER_COL_PAGE_START = 0x10,
    CMD_SSD1306_ADDRESS_MODE = 0x20,
    CMD_SSD1306_COL_ADDR = 0x21,
    CMD_SSD1306_PAGE_ADDR = 0x22,
    CMD_SSD1306_PAGE_START_PAGE_MODE = 0xB0,


    // Hardware configuration command table
    CMD_SSD1306_DISPLAY_START_LINE = 0x40,
    CMD_SSD1306_SEG_REMAP_0 = 0xA0,
    CMD_SSD1306_SEG_REMAP_127 = 0xA1,
    CMD_SSD1306_MUX_RATIO = 0xA8,
    CMD_SSD1306_ = 0x0,
    CMD_SSD1306_ = 0x0,
    CMD_SSD1306_ = 0x0,


    // Timing & driving scheme setting command table
    CMD_SSD1306_ = 0x0,
    CMD_SSD1306_ = 0x0,
    CMD_SSD1306_ = 0x0,
    CMD_SSD1306_ = 0x0,







}CMD_SSD1306_e;[]



typedef RS_CODE_e (*SSD1306_WriteReg_Func)(void *, uint8_t, uint8_t*, uint32_t);

typedef struct
{
  SSD1306_WriteReg_Func   WriteReg;
  void                *handle;
} SSD1306_ctx_s;

#endif