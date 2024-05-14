#include "screen.h"

static uint8_t screenState;
static uint8_t keyState;
uint8_t displayCount;

void screen_init(uint8_t count){
    screenState = 0;
    keyState = 0;
    displayCount = count;
}

void screen_update(){
    uint32_t display = 0;
    char hbtFlag[] = "X";
    RS_RGB565_e color;

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


void display_keyboard_callback(mpBase_t *mp, mpSubscriber_t *sub){
    MPKeyboardData_t data;
    GfxViewport_s viewport = {.displayID = 1, .originX = 0, .originY = 0, .pxWidth = 128, .pxHeight = 128};
    char hbtFlag[] = "X";
    switch(keyState & 0x3){
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

    display_draw_rect(1, 0, 0, 128, 128, RS_RGB565_BLACK);

    gfx_draw_text(&viewport, FONT_COURIER_10, hbtFlag);
    viewport.originY += 16;
    keyState++;

    RS_BOOL_e numBar;
    char initial[7] = {0};
    char vowel[7] = {5};
    char final[10] = {0};

    if(RS_CODE_OK != mp_get_data(mp, &data, sizeof(MPKeyboardData_t), critical_section)){
        gfx_draw_text(&viewport, FONT_COURIER_10, "Error");
        return;
    }
    


    if(RS_CODE_OK != keyboard_state_to_str(&data, &numBar, initial, vowel, final)){
        gfx_draw_text(&viewport, FONT_COURIER_10, "X");
        return;
    }

    if(numBar == RS_TRUE){
        gfx_draw_text(&viewport, FONT_COURIER_10, "#");
        viewport.originY += 15;
    }

    gfx_draw_text(&viewport, FONT_COURIER_10, initial);
    viewport.originY += 15;

    gfx_draw_text(&viewport, FONT_COURIER_10, vowel);
    viewport.originY += 15;

    gfx_draw_text(&viewport, FONT_COURIER_10, final);






}