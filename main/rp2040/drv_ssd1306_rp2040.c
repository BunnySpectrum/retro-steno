#include "hw/drv_ssd1306.h"
#include "hw/ssd1306.h"
#include "hw/ssd1306_reg.h"


static SSD1306_Object_s driverObjects[MAX_NUM_SSD1306];

RC_SSD1306_e rs_ssd1306_write_cmd(void *pCtx, uint8_t *pData, uint32_t length){
    DISP_CTX_SSD1306_s *pDriver = (DISP_CTX_SSD1306_s*) pCtx;
    i2cResponse_t resp;
    resp.data = pData;
    resp.length = length;


    rs_i2c_write(pDriver->i2cID, pDriver->i2cAddr, &resp, 0);
    

    return RC_SSD1306_OK;
}



RS_CODE_e rs_ssd1306_init(DISP_CTX_SSD1306_s *pCtx){
    // pass in display context then use that to look up the SSD1306 object
    if (pCtx->objID >= MAX_NUM_SSD1306){
        return RS_CODE_ERR;
    }
    SSD1306_Object_s *pObj = &driverObjects[pCtx->objID];

    pObj->ctx.WriteCmd = rs_ssd1306_write_cmd;
    pObj->ctx.handle = pCtx;

    pCtx->pDriver = pObj;



    // ST7735_Init(pObj, pCtx->colorCoding, pCtx->orientation);

    // uint32_t count;

    // // fill full RAM with black
    // ST7735_FillRect(pObj, 0, 0, ST7735_WIDTH, ST7735_HEIGHT, RS_RGB565_BLACK);

}

RS_CODE_e rs_ssd1306_reset(DISP_CTX_SSD1306_s *pCtx){
    DISP_CTX_SSD1306_s *pDriver = (DISP_CTX_SSD1306_s*) pCtx;
    uint8_t cmdDisplayOff[2] = {0x0, 0xAE};

    pCtx->pDriver->ctx.WriteCmd(pCtx->pDriver->ctx.handle, cmdDisplayOff, sizeof(cmdDisplayOff));

    return RS_CODE_OK;
}
