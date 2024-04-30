
#include "display.h"

static Logger_s displayPrinter;
static uint8_t displayID;

void set_logger_display(Logger_s printer){
    displayPrinter = printer;
}

void display_reset(){
    rs_gpio_put(DISP_RST_PIN, RS_FALSE);
    sleep_ms(100);
    rs_gpio_put(DISP_RST_PIN, RS_TRUE);
}

#define DISP_WIDTH 130
#define DISP_HEIGHT 132


void display_init(uint8_t spiID, uint8_t driverID){
    rs_st7735_init(spiID, driverID);
    
    // FIXME: origin changes based on orientation 
    uint8_t originX, originY;
    originX = DISP_ORIGIN_X;
    originY = DISP_ORIGIN_Y;

    // Top left
    rs_st7735_set_pixel(driverID, originX, originY, RS_RGB565_WHITE);
    
    // Top right
    rs_st7735_set_pixel(driverID, originX+127, originY, RS_RGB565_WHITE);

    // bottom right
    rs_st7735_set_pixel(driverID, originX+127, originY+127, RS_RGB565_WHITE);

    // bottom left
    rs_st7735_set_pixel(driverID, originX, originY+127, RS_RGB565_WHITE);

    rs_st7735_fill_rect(driverID, originX + 48, originY + 48, 32, 32, RS_RGB565_MAGENTA);

}

