
#include "display.h"

static Logger_s displayPrinter;
static uint8_t displayID;

void set_logger_display(Logger_s printer){
    displayPrinter = printer;
}

void display_reset(){
    rs_gpio_put(DISP0_RST_PIN, RS_FALSE);
    sleep_ms(100);
    rs_gpio_put(DISP0_RST_PIN, RS_TRUE);
}

#define DISP_WIDTH 130
#define DISP_HEIGHT 132


void z_display_init(DISP_CTX_s *pCtx){
    rs_st7735_init((DISP_CTX_ST7735_s*)pCtx->driverCtx);
    
    // FIXME: origin changes based on orientation 
    uint8_t originX, originY;
    originX = DISP_ORIGIN_X;
    originY = DISP_ORIGIN_Y;

    uint32_t driverID = pCtx->objID;

    // Top left
    rs_st7735_draw_pixel(driverID, originX, originY, RS_RGB565_WHITE);
    
    // Top right
    rs_st7735_draw_pixel(driverID, originX+127, originY, RS_RGB565_WHITE);

    // bottom right
    rs_st7735_draw_pixel(driverID, originX+127, originY+127, RS_RGB565_WHITE);

    // bottom left
    rs_st7735_draw_pixel(driverID, originX, originY+127, RS_RGB565_WHITE);

    if(driverID == 0){
        rs_st7735_draw_rect(driverID, 10+originX + 48, 10+originY + 48, 32, 32, RS_RGB565_RED);
        rs_st7735_draw_rect(driverID, originX + 48, originY + 48, 32, 32, RS_RGB565_BLUE);

    }else{
        rs_st7735_draw_rect(driverID, originX + 48, originY + 48, 32, 32, RS_RGB565_BLUE);
        rs_st7735_draw_rect(driverID, 10+originX + 48, 10+originY + 48, 32, 32, RS_RGB565_RED);

    }

}


void display_init(DISP_CTX_s *ctxList[], uint32_t length){
    uint32_t idx;

    for(idx = 0; idx<length; idx++){
        z_display_init(ctxList[idx]);
    }
}