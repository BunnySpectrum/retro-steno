#ifndef _GFX_CORE_H_
#define _GFX_CORE_H_

#include "bsp/display.h"
#include "app/gfx/gfx_font.h"
#include "app/gfx/fonts/font_manifest.h"
#include "utils/rs_codes.h"


RS_CODE_e gfx_draw_text(FontName_e, char* text);


RS_CODE_e get_glyph_for_index(FontName_e name, char code, const char** pBitmap, uint8_t* length, uint8_t* width, uint8_t* height);
RS_CODE_e gfx_font_get_text_metrics(FontName_e name);

#endif
