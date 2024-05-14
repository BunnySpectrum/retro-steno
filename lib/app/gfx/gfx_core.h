#ifndef _GFX_CORE_H_
#define _GFX_CORE_H_

#include "bsp/display.h"
#include "app/gfx/gfx_font.h"
#include "app/gfx/fonts/font_manifest.h"
#include "utils/rs_codes.h"
#include "utils/rs_string.h"
#include "utils/rs_macros.h"

#define MAX_VIEWPORT_WIDTH 128
#define MAX_VIEWPORT_HEIGHT 128

typedef struct GfxViewport{
    uint32_t displayID;
    uint16_t originX;
    uint16_t originY;
    uint16_t pxWidth;
    uint16_t pxHeight;
} GfxViewport_s;

static RS_RGB565_e gfxImageBuffer[MAX_VIEWPORT_WIDTH * MAX_VIEWPORT_HEIGHT];

RS_CODE_e gfx_draw_text(const GfxViewport_s *viewport, FontName_e fontName, char *text);


RS_CODE_e get_glyph_for_index(FontName_e name, char code, const char** pBitmap, uint8_t* length, uint8_t* width, uint8_t* height);
RS_CODE_e gfx_font_get_text_metrics(FontName_e name, const TextMetrics_s **tm);

#endif
