
#include "display.h"

static Logger_s displayPrinter;
static uint8_t displayID;
static DISP_CTX_s* displayContexts[MAX_NUM_DISPLAYS];
static uint32_t activeDisplays;

void set_logger_display(Logger_s printer){
    displayPrinter = printer;
}

void display_init(){
    activeDisplays = 0;
}

void display_reset(){
    rs_gpio_put(DISP0_RST_PIN, RS_FALSE);
    rs_sleep_ms(100);
    rs_gpio_put(DISP0_RST_PIN, RS_TRUE);
}

#define DISP_WIDTH 130
#define DISP_HEIGHT 132


void add_display(DISP_CTX_s *pCtx){
    // temp hack until common generic driver struct is made
    if(pCtx->objID < 2){
        rs_st7735_init((DISP_CTX_ST7735_s*)pCtx->driverCtx);
    }else{
        rs_ssd1306_init((DISP_CTX_SSD1306_s*)pCtx->driverCtx);
    }

    displayContexts[activeDisplays] = pCtx;
    activeDisplays++;

}


void add_displays(DISP_CTX_s *ctxList[], uint32_t length){
    uint32_t idx;

    for(idx = 0; idx<length; idx++){
        add_display(ctxList[idx]);
    }
}


RS_CODE_e display_draw_pixel(uint32_t displayID, uint32_t x, uint32_t y, RS_RGB565_e color){
    if(displayID >= activeDisplays){
        return RS_CODE_ERR;
    }
    
    DISP_CTX_s *dispCtx = displayContexts[displayID]; 
    return rs_st7735_draw_pixel(dispCtx->objID, DISP_ORIGIN_X + x, DISP_ORIGIN_Y + y, color);

}
RS_CODE_e display_draw_rect(uint32_t displayID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e color){
    if(displayID >= activeDisplays){
        return RS_CODE_ERR;
    }

    DISP_CTX_s *dispCtx = displayContexts[displayID]; 
    return rs_st7735_draw_rect(dispCtx->objID, DISP_ORIGIN_X + x, DISP_ORIGIN_Y + y, width, height, color);

}

RS_CODE_e display_draw_rect_bit(uint32_t displayID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e* pColors){
    if(displayID >= activeDisplays){
        return RS_CODE_ERR;
    }

    DISP_CTX_s *dispCtx = displayContexts[displayID]; 
    return rs_st7735_draw_rect_bit(dispCtx->objID, DISP_ORIGIN_X + x, DISP_ORIGIN_Y + y, width, height, pColors);

}

RS_CODE_e get_metrics_for_display(uint32_t displayID, const DisplayMetrics_s **metrics){
    if(displayID >= activeDisplays){
        return RS_CODE_ERR;
    }

    DISP_CTX_s *dispCtx = displayContexts[displayID]; 
    switch(dispCtx->name){
        case ADAFRUIT_TFT_128x128px_26mm4x26mm5:
            *metrics = &dm_adafruit_tft_128x128px_26mm4x26mm5;
            break;
        default:
            return RS_CODE_ERR;
    }

    return RS_CODE_OK;

}