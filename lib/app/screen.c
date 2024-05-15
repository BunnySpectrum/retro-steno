#include "screen.h"

static uint8_t screenState;
static uint8_t keyState;
uint8_t displayCount;

void screen_init(uint8_t count){
    screenState = 0;
    keyState = 0;
    displayCount = count;
    
    const TextMetrics_s *tm;
    DisplayMetrics_s dm;
    if(RS_CODE_OK != gfx_font_get_text_metrics(FONT_COURIER_10, &tm)){
        return;
    }
    
    if(RS_CODE_OK != get_metrics_for_display(1, &dm)){
        return;
    }
    display_draw_rect(1, 0, 0, dm.pxWidth, dm.pxHeight, RS_RGB565_WHITE);
}

void screen_update(){
    uint32_t display = 0;
    char hbtFlag[] = "X";
    RS_RGB565_e color;
    const TextMetrics_s *tm;
    DisplayMetrics_s dm;
    uint32_t activeDisplay = 0;

    if(RS_CODE_OK != gfx_font_get_text_metrics(FONT_COURIER_10, &tm)){
        return;
    }
    
    if(RS_CODE_OK != get_metrics_for_display(activeDisplay, &dm)){
        return;
    }

    GfxViewport_s viewport = {.displayID = 0, .originX = 0, .originY = 0, .pxWidth = 128, .pxHeight = 128};
    GfxViewport_s vpFlag = {.displayID = activeDisplay, .originX = dm.pxWidth - tm->maxCharWidth, .originY = dm.pxHeight - tm->height, .pxWidth = dm.pxWidth, .pxHeight = dm.pxHeight};

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

    vpFlag.originX = rand() % (dm.pxWidth - tm->maxCharWidth);
    vpFlag.originY = rand() % (dm.pxHeight - tm->height);

    display_draw_rect(activeDisplay, 0, 0, dm.pxWidth, dm.pxHeight, RS_RGB565_BLACK);
    
    gfx_draw_text(&vpFlag, FONT_COURIER_10, hbtFlag);

    // display_draw_rect(0, 0, 0, 1, 128, RS_RGB565_RED);
    // gfx_draw_text(&viewport, FONT_COURIER_10, "#");
    // viewport.originY += tm->height;

    // gfx_draw_text(&viewport, FONT_COURIER_10, "STKPWHR");
    // viewport.originY += tm->height;

    // gfx_draw_text(&viewport, FONT_COURIER_10, "AO*EU");
    // viewport.originY += tm->height;

    // gfx_draw_text(&viewport, FONT_COURIER_10, "FRPBLGTSDZ");


    screenState++;
}


void display_keyboard_callback(mpBase_t *mp, mpSubscriber_t *sub){
    MPKeyboardData_t data;
    const TextMetrics_s *tm;
    DisplayMetrics_s dm;
    uint32_t activeDisplay = 1;
    uint16_t startingY = 4;
    static uint16_t line = 4;

    if(RS_CODE_OK != gfx_font_get_text_metrics(FONT_COURIER_10, &tm)){
        return;
    }
    
    if(RS_CODE_OK != get_metrics_for_display(activeDisplay, &dm)){
        return;
    }

    GfxViewport_s viewport = {.displayID = activeDisplay, .originX = tm->maxCharWidth, .originY = line, .pxWidth = dm.pxWidth, .pxHeight = dm.pxHeight};
    GfxViewport_s vpFlag = {.displayID = activeDisplay, .originX = dm.pxWidth - tm->maxCharWidth, .originY = 0, .pxWidth = dm.pxWidth, .pxHeight = dm.pxHeight};
    GfxViewport_s vpCursor = {.displayID = activeDisplay, .originX = 0, .originY = line, .pxWidth = dm.pxWidth, .pxHeight = dm.pxHeight};

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


    gfx_draw_text(&vpFlag, FONT_COURIER_10, hbtFlag);
    keyState++;

    RS_BOOL_e numBar;
    char initial[7] = {0};
    char vowel[5] = {0};
    char final[10] = {0};

    uint8_t charRead, charWrite, chordIdx;
    uint16_t textScreenWidth, textScreenHeight;
    char cVal;
    char initialShort[7] = {0};
    char vowelShort[5] = {0};
    char finalShort[10] = {0};
    char fullChord[1 + 7 + 5 + 10] = {0};
    chordIdx = 0;

    if(RS_CODE_OK != mp_get_data(mp, &data, sizeof(MPKeyboardData_t), critical_section)){
        gfx_draw_text(&viewport, FONT_COURIER_10, "Error");
        return;
    }
    


    if(RS_CODE_OK != keyboard_state_to_str(&data, &numBar, initial, vowel, final)){
        gfx_draw_text(&viewport, FONT_COURIER_10, "X");
        return;
    }
        

    if(numBar == RS_TRUE){
        // gfx_draw_text(&viewport, FONT_COURIER_10, "#");
        fullChord[chordIdx++] = '#';
    }
    // viewport.originY += tm->height;

    // gfx_draw_text(&viewport, FONT_COURIER_10, initial);
    // viewport.originY += tm->height;

    // gfx_draw_text(&viewport, FONT_COURIER_10, vowel);
    // viewport.originY += tm->height;

    // gfx_draw_text(&viewport, FONT_COURIER_10, final);
    // viewport.originY += tm->height*2;


    charRead = charWrite = 0;
    cVal = initial[charRead];
    while(cVal != '\0'){
        if(cVal != ' '){
            initialShort[charWrite++] = cVal;
            fullChord[chordIdx++] = cVal;
        }
        charRead++;
        cVal = initial[charRead];
    }
    initialShort[charWrite] = '\0';
    fullChord[chordIdx++] = '|';
    // gfx_draw_text(&viewport, FONT_COURIER_10, initialShort);
    // viewport.originY += tm->height;


    charRead = charWrite = 0;
    cVal = vowel[charRead];
    while(cVal != '\0'){
        if(cVal != ' '){
            vowelShort[charWrite++] = cVal;
            fullChord[chordIdx++] = cVal;
        }
        charRead++;
        cVal = vowel[charRead];
    }
    vowelShort[charWrite] = '\0';
    fullChord[chordIdx++] = '|';
    // gfx_draw_text(&viewport, FONT_COURIER_10, vowelShort);
    // viewport.originY += tm->height;


    charRead = charWrite = 0;
    cVal = final[charRead];
    while(cVal != '\0'){
        if(cVal != ' '){
            finalShort[charWrite++] = cVal;
            fullChord[chordIdx++] = cVal;
        }
        charRead++;
        cVal = final[charRead];
    }
    finalShort[charWrite] = '\0';
    // gfx_draw_text(&viewport, FONT_COURIER_10, finalShort);
    // viewport.originY += tm->height;


    fullChord[chordIdx] = '\0';

    // Clear cursor
    display_draw_rect(activeDisplay, 0, 0, tm->maxCharWidth, dm.pxHeight, RS_RGB565_WHITE);

    // Calc how much space text will take
    if(RS_CODE_OK != gfx_text_extents(&viewport, FONT_COURIER_10, fullChord, &textScreenWidth, &textScreenHeight)){
        return;
    }

    if( (line + textScreenHeight) > dm.pxHeight){
        display_draw_rect(activeDisplay, 0, viewport.originY, dm.pxWidth, dm.pxHeight - viewport.originY, RS_RGB565_WHITE);
        line = startingY;
        viewport.originY = line;
        vpCursor.originY = line;
    }

    // Clear section
    display_draw_rect(activeDisplay, 0, viewport.originY, dm.pxWidth, textScreenHeight, RS_RGB565_WHITE);

    // Draw cursor
    printf("Cursor: Y %d, line %d\n", vpCursor.originY, line);
    gfx_draw_text(&vpCursor, FONT_COURIER_10, ">");
    gfx_draw_text(&viewport, FONT_COURIER_10, fullChord);
    line = (line + textScreenHeight);

}