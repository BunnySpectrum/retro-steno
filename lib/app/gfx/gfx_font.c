
#include "app/gfx/gfx_font.h"

RS_CODE_e get_glyph_for_index(FontName_e name, uint8_t index, const char** offset, uint8_t* length, uint8_t* width, uint8_t* height){
    if(index >= 224){ //courier 10 is 2912 bytes, every 13 represents one glyph, so we have 2912/13 = 224 glyphs
        return RS_CODE_ERR;
    }

    *length = 13;
    *width = 8;
    *height = 13;
    *offset = &font_Courier_10[index*13];

    return RS_CODE_OK;
}