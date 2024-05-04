#include "hw/drv_st7735.h"

#include "st7735.h"
#include "st7735_reg.h"

static uint8_t SPI_ID_ST7735;
static ST7735_Object_t driverObjects[MAX_NUM_DISPLAY_DRIVERS];
// static ST7735_IO_t driverIOs[MAX_NUM_DISPLAY_DRIVERS];

int32_t rs_st7735_write_reg(void *pCtx, uint8_t reg, uint8_t *pData, uint32_t length){
    return ST7735_ERROR;
}

int32_t nop_rs_st7735_write_reg(uint8_t reg, uint8_t *pData, uint32_t length){
    return ST7735_ERROR;
}



int32_t rs_st7735_read_reg(void *pCtx, uint8_t reg, uint8_t *pData){
    return ST7735_ERROR;
}

int32_t nop_rs_st7735_read_reg(uint8_t reg, uint8_t *pData){
    return ST7735_ERROR;
}

int32_t rs_st7735_send_data(void *pCtx, uint8_t *pData, uint32_t length){
    return ST7735_ERROR;
}

int32_t nop_rs_st7735_send_data(uint8_t *pData, uint32_t length){
    return ST7735_ERROR;
}

int32_t rs_st7735_recv_data(void *pCtx, uint8_t *pData, uint32_t length){
    return ST7735_ERROR;
}

int32_t nop_rs_st7735_recv_data(uint8_t *pData, uint32_t length){
    return ST7735_ERROR;
}

int32_t rs_st7735_get_tick(){
    return ST7735_ERROR;
}



int32_t rs_st7735_io_init(){
    return ST7735_ERROR;
}

int32_t rs_st7735_io_deinit(){
    return ST7735_ERROR;
}

RS_CODE_e rs_st7735_init(DISP_CTX_ST7735_s *pCtx){
    return ST7735_ERROR;
}

RS_CODE_e rs_st7735_draw_pixel(uint8_t driverID, uint32_t x, uint32_t y, RS_RGB565_e color){
    return ST7735_ERROR;
}


RS_CODE_e rs_st7735_draw_rect(uint8_t driverID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e color){
    return ST7735_ERROR;
}

RS_CODE_e rs_st7735_draw_rect_bit(uint8_t driverID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e* pColors){
    return ST7735_ERROR;
}
