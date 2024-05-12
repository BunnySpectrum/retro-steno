#include "app/gfx/gfx_core.h"


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