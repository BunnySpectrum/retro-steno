#include "app/gfx/gfx_core.h"


RS_CODE_e gfx_draw_text(const GfxViewport_s *viewport, FontName_e fontName, char *text){
    RS_CODE_e result;
    char glyph;
    size_t textIdx;

    const char* pBitmap;
    uint8_t length, width, height, bitmapIndex, bitmapRow, bitmapCol, bitmapValue;
    uint16_t drawX, drawY;

    DisplayMetrics_s displayMetrics;
    if(RS_CODE_OK != get_metrics_for_display(viewport->displayID, &displayMetrics)){
        return RS_CODE_ERR;
    }

    drawX = viewport->originX;
    drawY = viewport->originY;
    for(textIdx = 0; textIdx < rs_strlen(text); textIdx++){
        glyph = text[textIdx];
        result = get_glyph_for_index(fontName, glyph, &pBitmap, &length, &width, &height);

        // Check if glyph will fit on this line
        // X is 0-based index, width is a count of pixels
        // so a 8-wide glyph drawn at X is legal so long as X + width is <= maxWidth
        if( ((drawX + width) > RS_MIN(viewport->pxWidth + viewport->originX, displayMetrics.pxWidth) )){
            // need to wrap
            drawX = viewport->originX;
            drawY += height; 
        }

        // for now, if we exceed the viewport just bail with error
        if((drawY + height) > RS_MIN(viewport->pxHeight + viewport->originY, displayMetrics.pxHeight)){
            return RS_CODE_ERR;
        }


        // Check for bounds 
        if(((drawX + width - viewport->originX) > MAX_VIEWPORT_WIDTH) || ((drawY + height - viewport->originY) > MAX_VIEWPORT_HEIGHT)){
            return RS_CODE_ERR;
        }

        if(((drawX + width) > displayMetrics.pxWidth) || ((drawY + height) > displayMetrics.pxHeight)){
            return RS_CODE_ERR;
        }





        for(bitmapIndex=0; bitmapIndex < width*height; bitmapIndex++){
            bitmapRow = bitmapIndex / 8;
            bitmapCol = bitmapIndex % 8;
            bitmapValue = (pBitmap[bitmapRow] >> ((width-1)-bitmapCol)) & (0x01);
            gfxImageBuffer[(bitmapRow)*width + (bitmapCol)] = bitmapValue == 1 ? RS_RGB565_BLACK : RS_RGB565_WHITE;
        }


        display_draw_rect_bit(viewport->displayID, drawX, drawY, width, height, gfxImageBuffer);

        drawX += width;

    }

    return RS_CODE_OK;

}


static RS_CODE_e get_font_objs_by_name(FontName_e name, const char** bitmap, const TextMetrics_s ** tm){
    switch(name){
        case FONT_COURIER_10:
            *bitmap = font_win31_courier_e_10;
            *tm = &tm_win31_courier_e_10;
            return RS_CODE_OK;

        case FONT_COURIER_12:
            return RS_CODE_ERR;

        case FONT_COURIER_15:
            return RS_CODE_ERR;

        default:
            return RS_CODE_ERR;

    }
    return RS_CODE_OK;
}

RS_CODE_e gfx_font_get_text_metrics(FontName_e name, const TextMetrics_s **tm){
    switch(name){
        case FONT_COURIER_10:
            *tm = &tm_win31_courier_e_10;
            return RS_CODE_OK;

        case FONT_COURIER_12:
            return RS_CODE_ERR;

        case FONT_COURIER_15:
            return RS_CODE_ERR;

        default:
            return RS_CODE_ERR;

    }
    return RS_CODE_OK;

}

RS_CODE_e get_glyph_for_index(FontName_e name, char code, const char** offset, uint8_t* length, uint8_t* width, uint8_t* height){
    const char* data;
    const TextMetrics_s *tm;

    if(RS_CODE_OK != get_font_objs_by_name(name, &data, &tm)){
        return RS_CODE_ERR;
    }

    if((code < tm->firstChar) || (code > tm->lastChar)){ 
        code = tm->defaultChar;
    }

    // NB works only for fixed width fonts
    *length = (tm->maxCharWidth * tm->height) / 8;
    *width = tm->maxCharWidth;
    *height = tm->height;
    *offset = &data[(code - tm->firstChar) * (*length)];

    return RS_CODE_OK;
}