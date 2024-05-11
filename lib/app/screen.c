#include "screen.h"

uint8_t screenState;
uint8_t displayCount;

void screen_init(uint8_t count){
    screenState = 0;
    displayCount = count;
}

void screen_update(){
    uint8_t display = 0;
    RS_RGB565_e color;

    for(display = 0; display < displayCount; display++){
        display_draw_rect(display, 0, 0, 32, 32, RS_RGB565_BLACK);
        display_draw_rect(display, 32, 32, 32, 32, RS_RGB565_BLACK);
    }

    if(screenState == 0){
        for(display = 0; display < displayCount; display++){
            rgb565_for_index((display % (RGB565_COLOR_COUNT-1)) + 1, &color);

            display_draw_rect(display, 0, 0, 32, 32, color);
        }
    }else{
        for(display = 0; display < displayCount; display++){
            rgb565_for_index(((display+2) % (RGB565_COLOR_COUNT-1)) + 1, &color);
            display_draw_rect(display, 32, 32, 32, 32, color);
        }
    }
    screenState ^= 0x1;
}