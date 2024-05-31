
#include "hw/ssd1306.h"

RC_SSD1306_e ssd1306_init(SSD1306_Object_s *pObj, uint32_t orientation, uint32_t height){
    uint8_t cmdDisplayOff[2] = {0x0, 0xAE};
    uint8_t cmdSetDisplayClockDiv1[2] = {0x0, 0xD5};
    uint8_t cmdSetDisplayClockDiv2[2] = {0x0, 0x80};
    uint8_t cmdSetMultiplex[2] = {0x0, 0xA8};
    uint8_t cmdHeight[2] = {0x0, height};

    uint8_t cmdDisplayOffset1[2] = {0x0, 0xD3};
    uint8_t cmdDisplayOffset2[2] = {0x0, 0x0};
    uint8_t cmdSetStartline[2] = {0x0, 0x40 | 0x0};
    uint8_t cmdChargepump[2] = {0x0, 0x8D};
    uint8_t cmdVCC1[2] = {0x0, 0x14};

    uint8_t cmdMemoryMode1[2] = {0x0, 0x20};
    uint8_t cmdMemoryMode2[2] = {0x0, 0x00};
    uint8_t cmdSegremap[2] = {0x0, 0xA0 | 0x1};
    uint8_t cmdComscandev[2] = {0x0, 0xC8};

    // More hacking until I have a notion of panel config
    uint8_t comPins = height == 63 ? 0x12 : 0x02;
    uint8_t contrast = 0x8F;

    uint8_t cmdSetcompins1[2] = {0x0, 0xDA};
    uint8_t cmdSetcompins2[2] = {0x0, comPins};
    uint8_t cmdSetcontrast1[2] = {0x0, 0x81};
    uint8_t cmdSetcontrast2[2] = {0x0, contrast};
    uint8_t cmdSetprecharge1[2] = {0x0, 0xD9};
    uint8_t cmdSetprecharge2[2] = {0x0, 0xF1};

    uint8_t cmdSetvcomdetect1[2] = {0x0, 0xD8};
    uint8_t cmdSetvcomdetect2[2] = {0x0, 0x40};
    uint8_t cmdDisplayAllOnResume[2] = {0x0, 0xA4};
    uint8_t cmdNormalDisplay[2] = {0x0, 0xA6};
    uint8_t cmdDeactivatescroll[2] = {0x0, 0x2E};
    uint8_t cmdDisplayOn[2] = {0x0, 0xAF};

    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdDisplayOff, sizeof(cmdDisplayOff));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSetDisplayClockDiv1, sizeof(cmdSetDisplayClockDiv1));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSetDisplayClockDiv2, sizeof(cmdSetDisplayClockDiv2));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSetMultiplex, sizeof(cmdSetMultiplex));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdHeight, sizeof(cmdHeight));

    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdDisplayOffset1, sizeof(cmdDisplayOffset1));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdDisplayOffset2, sizeof(cmdDisplayOffset2));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSetStartline, sizeof(cmdSetStartline));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdChargepump, sizeof(cmdChargepump));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdVCC1, sizeof(cmdVCC1));

    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdMemoryMode1, sizeof(cmdMemoryMode1));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdMemoryMode2, sizeof(cmdMemoryMode2));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSegremap, sizeof(cmdSegremap));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdComscandev, sizeof(cmdComscandev));


    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSetcompins1, sizeof(cmdSetcompins1));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSetcompins2, sizeof(cmdSetcompins2));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSetcontrast1, sizeof(cmdSetcontrast1));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSetcontrast2, sizeof(cmdSetcontrast2));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSetprecharge1, sizeof(cmdSetprecharge1));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSetprecharge2, sizeof(cmdSetprecharge2));


    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSetvcomdetect1, sizeof(cmdSetvcomdetect1));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdSetvcomdetect2, sizeof(cmdSetvcomdetect2));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdDisplayAllOnResume, sizeof(cmdDisplayAllOnResume));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdNormalDisplay, sizeof(cmdNormalDisplay));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdDeactivatescroll, sizeof(cmdDeactivatescroll));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdDisplayOn, sizeof(cmdDisplayOn));


    uint8_t cmdPageaddr1[2] = {0x00, 0x22};
    uint8_t cmdPageaddr2[2] = {0x00, 0x0};
    uint8_t cmdPageaddr3[2] = {0x00, 0xFF};
    uint8_t cmdColumnaddr1[2] = {0x00, 0x21};
    uint8_t cmdColumnaddr2[2] = {0x00, 0};
    uint8_t cmdWidth[2] = {0x00, 127};

    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdPageaddr1, sizeof(cmdPageaddr1));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdPageaddr2, sizeof(cmdPageaddr2));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdPageaddr3, sizeof(cmdPageaddr3));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdColumnaddr1, sizeof(cmdColumnaddr1));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdColumnaddr2, sizeof(cmdColumnaddr2));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdWidth, sizeof(cmdWidth));






    uint8_t dataPixel[2] = {0x40, 0xFF};

    for(int i = 0; i < 128 * ((height+7) / 8); i++){
        dataPixel[1] = 0xff;
        pObj->ctx.WriteCmd(pObj->ctx.handle, dataPixel, sizeof(dataPixel));
    }


    return RC_SSD1306_OK;


}

RC_SSD1306_e ssd1306_set_pixel(SSD1306_Object_s *pObj, uint32_t x, uint32_t y, uint32_t color){
    uint8_t page = y/8;
    // uint8_t page = (y % 2) == 0 ? y/8 : y/8 + 4;
    uint8_t rowWithinPage = y % 8;

    uint8_t cmdPageaddr1[2] = {0x00, 0x22};
    uint8_t cmdPageaddr2[2] = {0x00, page+color};
    uint8_t cmdPageaddr3[2] = {0x00, page+color};
    uint8_t cmdColumnaddr1[2] = {0x00, 0x21};
    uint8_t cmdColumnaddr2[2] = {0x00, x};
    uint8_t cmdWidth[2] = {0x00, x};
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdPageaddr1, sizeof(cmdPageaddr1));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdPageaddr2, sizeof(cmdPageaddr2));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdPageaddr3, sizeof(cmdPageaddr3));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdColumnaddr1, sizeof(cmdColumnaddr1));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdColumnaddr2, sizeof(cmdColumnaddr2));
    pObj->ctx.WriteCmd(pObj->ctx.handle, cmdWidth, sizeof(cmdWidth));
    
    uint8_t dataPixel[2] = {0x40, 0xFF};
    dataPixel[1] = (1<<rowWithinPage)^0xFF;
    pObj->ctx.WriteCmd(pObj->ctx.handle, dataPixel, sizeof(dataPixel));

    return RC_SSD1306_OK;
}

RC_SSD1306_e ssd1306_fill_rect(SSD1306_Object_s *pObj, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color){
    return RC_SSD1306_ERR;
}

RC_SSD1306_e ssd1306_bitmap_rect(SSD1306_Object_s *pObj, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t* pColors){
    return RC_SSD1306_ERR;
}