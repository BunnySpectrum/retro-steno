#include "screen.h"

uint8_t screenState;
uint8_t textCounter;
uint8_t displayCount;

void screen_init(uint8_t count){
    screenState = 0;
    textCounter = 0;
    displayCount = count;
}

void screen_update(){
    uint32_t display = 0;
    char hbtFlag[] = "X";
    RS_RGB565_e color;

    for(display = 1; display < displayCount; display++){
        display_draw_rect(display, 0, 0, 32, 32, RS_RGB565_BLACK);
        display_draw_rect(display, 32, 32, 32, 32, RS_RGB565_BLACK);
    }

    if( (screenState & 0x1 ) == 0){
        for(display = 1; display < displayCount; display++){
            rgb565_for_index((display % (RGB565_COLOR_COUNT-1)) + 1, &color);

            display_draw_rect(display, 0, 0, 32, 32, color);
        }
    }else{
        for(display = 1; display < displayCount; display++){
            rgb565_for_index(((display+2) % (RGB565_COLOR_COUNT-1)) + 1, &color);
            display_draw_rect(display, 32, 32, 32, 32, color);
        }
    }

    uint16_t index, row, col;

    for(row=0; row < 32; row++){
        for(col=0; col < 32; col++){
            index = row*32 + col;
            switch(row >> 3){
                case 0:
                    imageBuffer[index] = RS_RGB565_GREEN;
                    break;
                case 1:
                    imageBuffer[index] = RS_RGB565_BLUE;
                    break;
                case 2:
                    imageBuffer[index] = RS_RGB565_MAGENTA;
                    break;
                case 3:
                    imageBuffer[index] = RS_RGB565_CYAN;
                    break;
                default:
                    imageBuffer[index] = RS_RGB565_WHITE;
                    break;

            }
        }
    }

    switch(screenState & 0x3){
        case 0b00:
            hbtFlag[0] = '|';
            break;
        case 0b01:
            hbtFlag[0] = '/';
            break;
        case 0b10:
            hbtFlag[0] = '-';
            break;
        case 0b11:
            hbtFlag[0] = '\\';
            break;
        default:
            hbtFlag[0] = 'X';
    }


    GfxViewport_s viewport = {.displayID = 0, .originX = 0, .originY = 0, .pxWidth = 128, .pxHeight = 128};
    
    gfx_draw_text(&viewport, FONT_COURIER_10, hbtFlag);
    viewport.originY += 30;

    // display_draw_rect(0, 0, 0, 1, 128, RS_RGB565_RED);
    gfx_draw_text(&viewport, FONT_COURIER_10, "#");
    viewport.originY += 15;

    gfx_draw_text(&viewport, FONT_COURIER_10, "STKPWHR");
    viewport.originY += 15;

    gfx_draw_text(&viewport, FONT_COURIER_10, "AO*EU");
    viewport.originY += 15;

    gfx_draw_text(&viewport, FONT_COURIER_10, "FRPBLGTSDZ");


    screenState++;
}