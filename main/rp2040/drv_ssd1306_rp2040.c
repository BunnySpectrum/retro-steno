#include "hw/drv_ssd1306.h"
#include "hw/ssd1306.h"
#include "hw/ssd1306_reg.h"


static uint8_t I2C_ID_SSD1306;
static SSD1306_Object_s driverObjects[MAX_NUM_SSD1306];
// static ST7735_IO_t driverIOs[MAX_NUM_DISPLAY_DRIVERS];

int32_t rs_ssd1306_write_reg(void *pCtx, uint8_t reg, uint8_t *pData, uint32_t length){
    DISP_CTX_SSD1306_s *pDriver = (DISP_CTX_SSD1306_s*) pCtx;
    i2cResponse_t resp1, resp2;
    uint8_t data1[2] = {0x00, reg};
    resp1.data = data1;
    resp1.length = sizeof(data1);


    rs_i2c_write(pDriver->i2cID, pDriver->i2cAddr, &resp1, 0);
    
    if(length > 0){
        resp2.data = pData;
        resp2.length = length;

        rs_i2c_write(pDriver->i2cID, pDriver->i2cAddr, &resp2, 0);
    }

    return RS_CODE_OK;
}



RS_CODE_e rs_ssd1306_init(DISP_CTX_SSD1306_s *pCtx){
    if (pCtx->objID >= MAX_NUM_SSD1306){
        return RS_CODE_ERR;
    }
    SSD1306_Object_s *pObj = &driverObjects[pCtx->objID];

    pObj->IO.Init      = rs_st7735_io_init;
    pObj->IO.DeInit    = rs_st7735_io_deinit;
    pObj->IO.Address   = pCtx->objID;
    pObj->IO.WriteReg  = nop_rs_st7735_write_reg;
    pObj->IO.ReadReg   = nop_rs_st7735_read_reg;
    pObj->IO.SendData  = nop_rs_st7735_send_data;
    pObj->IO.RecvData  = nop_rs_st7735_recv_data;
    pObj->IO.GetTick   = rs_st7735_get_tick;

    pObj->Ctx.ReadReg   = rs_st7735_read_reg;
    pObj->Ctx.WriteReg  = rs_st7735_write_reg;
    pObj->Ctx.SendData  = rs_st7735_send_data;
    pObj->Ctx.RecvData  = rs_st7735_recv_data;
    pObj->Ctx.handle    = pCtx;

    pObj->IO.Init();
    pCtx->pDriver = pObj;



    ST7735_Init(pObj, pCtx->colorCoding, pCtx->orientation);

    uint32_t count;

    // fill full RAM with black
    ST7735_FillRect(pObj, 0, 0, ST7735_WIDTH, ST7735_HEIGHT, RS_RGB565_BLACK);

    // sleep_ms(200);
    uint8_t pixel;




}

RS_CODE_e rs_st7735_draw_pixel(uint8_t driverID, uint32_t x, uint32_t y, RS_RGB565_e color){
    if(driverID >= MAX_NUM_DISPLAY_DRIVERS){
        return RS_CODE_ERR;
    }

    ST7735_SetPixel(&driverObjects[driverID], x, y, color);
    // ST7735_SetPixel(&obj, x, y, color);
    return RS_CODE_OK;
}


RS_CODE_e rs_st7735_draw_rect(uint8_t driverID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e color){
    if(driverID >= MAX_NUM_DISPLAY_DRIVERS){
        return RS_CODE_ERR;
    }

    ST7735_FillRect(&driverObjects[driverID], x, y, width, height, color);
    // ST7735_FillRect(&obj, x, y, width, height, color);
    return RS_CODE_OK;
}

RS_CODE_e rs_st7735_draw_rect_bit(uint8_t driverID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e* pColors){
    if(driverID >= MAX_NUM_DISPLAY_DRIVERS){
        return RS_CODE_ERR;
    }

    ST7735_FillRGBRect(&driverObjects[driverID], x, y, (uint8_t*)pColors, width, height);
    return RS_CODE_OK;
}
