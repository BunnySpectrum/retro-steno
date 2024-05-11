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

    for(index = 0; index < 32*32; index++){
        imageBuffer[index] = RS_RGB565_CYAN;
    }

    row = 0;
    col = 0;

    const char* pBitmap;
    uint8_t length, width, height, bitmapIndex, bitmapRow, bitmapCol, bitmapValue;
    get_glyph_for_index(FONT_COURIER_10, 0x41 - 0x20 + textCounter, &pBitmap, &length, &width, &height);

    // for(bitmapRow=0; bitmapRow < height; bitmapRow++){
    //     for(bitmapCol=0; bitmapCol < width; bitmapCol++){
    //         bitmapValue = (pBitmap[bitmapRow] >> (7-bitmapCol)) & (0x01);
    //         imageBuffer[(row + bitmapRow)*32 + (col + bitmapCol)] = bitmapValue == 1 ? RS_RGB565_BLACK : RS_RGB565_WHITE;
    //     }
    // }

    for(bitmapIndex=0; bitmapIndex < width*height; bitmapIndex++){
        bitmapRow = bitmapIndex / 8;
        bitmapCol = bitmapIndex % 8;
        bitmapValue = (pBitmap[bitmapRow] >> ((width-1)-bitmapCol)) & (0x01);
        imageBuffer[(row + bitmapRow)*32 + (col + bitmapCol)] = bitmapValue == 1 ? RS_RGB565_BLACK : RS_RGB565_WHITE;
    }

    display_draw_rect_bit(0, 0, 32, 32, 32, imageBuffer);

    textCounter = (textCounter + 1) % 26; 






    screenState ^= 0x1;
}