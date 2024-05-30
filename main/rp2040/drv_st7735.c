#include "hw/drv_st7735.h"

#include "st7735.h"
#include "st7735_reg.h"

// static uint8_t SPI_ID_ST7735;
static ST7735_Object_t driverObjects[MAX_NUM_DISPLAY_DRIVERS];
// static ST7735_IO_t driverIOs[MAX_NUM_DISPLAY_DRIVERS];

int32_t rs_st7735_write_reg(void *pCtx, uint8_t reg, uint8_t *pData, uint32_t length){
    DISP_CTX_ST7735_s *pDriver = (DISP_CTX_ST7735_s*) pCtx;
    spiResponse_t resp1, resp2;
    uint8_t data1[1] = {reg};
    resp1.data = data1;
    resp1.length = 1;


    rs_gpio_put(pDriver->dispDCPin, 0);
    rs_gpio_put(pDriver->dispCSPin, 0);
    rs_spi_send_data(&resp1, pDriver->spiID);
    rs_gpio_put(pDriver->dispCSPin, 1);
    
    if(length > 0){
        resp2.data = pData;
        resp2.length = length;

        rs_gpio_put(pDriver->dispDCPin, 1);
        rs_gpio_put(pDriver->dispCSPin, 0);
        rs_spi_send_data(&resp2, pDriver->spiID);
        rs_gpio_put(pDriver->dispCSPin, 1);
    }

    return ST7735_OK;
}

int32_t nop_rs_st7735_write_reg(uint8_t reg, uint8_t *pData, uint32_t length){
    return ST7735_ERROR;
}



int32_t rs_st7735_read_reg(void *pCtx, uint8_t reg, uint8_t *pData){
    DISP_CTX_ST7735_s *pDriver = (DISP_CTX_ST7735_s*) pCtx;
    spiResponse_t resp1, resp2;
    uint8_t data1[2] = {reg, 0x0};
    uint8_t data2[2] = {0x0, 0x0};
    resp1.data = data1;
    resp1.length = 1;

    resp2.data = data2;
    resp2.length = 1;

    rs_gpio_put(pDriver->dispDCPin, 0);
    rs_gpio_put(pDriver->dispCSPin, 0);
    rs_spi_send_data(&resp1, pDriver->spiID);
    // need to hi-z MOSI and bit bang input maybe?
    rs_spi_recv_data(&resp2, pDriver->spiID, 0x0);
    rs_gpio_put(pDriver->dispCSPin, 1);


    *pData = resp2.data[0];

    return ST7735_OK;
}

int32_t nop_rs_st7735_read_reg(uint8_t reg, uint8_t *pData){
    return ST7735_ERROR;
}

int32_t rs_st7735_send_data(void *pCtx, uint8_t *pData, uint32_t length){
    DISP_CTX_ST7735_s *pDriver = (DISP_CTX_ST7735_s*) pCtx;
    spiResponse_t resp2;

    resp2.data = pData;
    resp2.length = length;

    rs_gpio_put(pDriver->dispDCPin, 1);
    rs_gpio_put(pDriver->dispCSPin, 0);
    rs_spi_send_data(&resp2, pDriver->spiID);
    rs_gpio_put(pDriver->dispCSPin, 1);

    return ST7735_OK;
}

int32_t nop_rs_st7735_send_data(uint8_t *pData, uint32_t length){
    return ST7735_ERROR;
}

int32_t rs_st7735_recv_data(void *pCtx, uint8_t *pData, uint32_t length){
    // If I can get read reg to work w/ this display (TBD if hardware limitation on display board), then I can implement this function
    return ST7735_ERROR;
}

int32_t nop_rs_st7735_recv_data(uint8_t *pData, uint32_t length){
    return ST7735_ERROR;
}

int32_t rs_st7735_get_tick(){
    return get_tick();
}



int32_t rs_st7735_io_init(){
    return ST7735_OK;
}

int32_t rs_st7735_io_deinit(){
    return ST7735_OK;
}

RS_CODE_e rs_st7735_init(DISP_CTX_ST7735_s *pCtx){
    if (pCtx->objID >= MAX_NUM_DISPLAY_DRIVERS){
        return RS_CODE_ERR;
    }
    ST7735_Object_t *pObj = &driverObjects[pCtx->objID];

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
