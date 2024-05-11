#ifndef _GFX_FONT_H_
#define _GFX_FONT_H_

#include "app/gfx/fonts/win31_courier_e_10.h"
#include "utils/rs_stdint.h"
#include "utils/rs_codes.h"

typedef struct FontGlyph{
    char code;
    char* bitmapOffset;
    uint16_t length;
}FontGlyph_s;

typedef enum FontName{
    FONT_COURIER_10,
    FONT_COURIER_12,
    FONT_COURIER_15,
} FontName_e;

RS_CODE_e get_glyph_for_index(FontName_e name, uint8_t index, const char** pBitmap, uint8_t* length, uint8_t* width, uint8_t* height);

#endif
