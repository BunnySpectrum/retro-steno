#ifndef _GFX_FONT_H_
#define _GFX_FONT_H_

#include "utils/rs_stdint.h"
#include "utils/rs_codes.h"

typedef struct FontGlyph{
    char code;
    char* bitmapOffset;
    uint16_t length;
}FontGlyph_s;



// https://learn.microsoft.com/en-us/dotnet/api/system.windows.forms.visualstyles.textmetricscharacterset
typedef enum FontCharSet{
    FONT_CHAR_SET_ANSI = 0,
    FONT_CHAR_SET_DEFAULT = 1,
}FontCharSet_e;

typedef enum FontPitchAndFamily{
    FONT_PITCH_FAMILY_FIXED = 0x01,
    FONT_PITCH_FAMILY_VECTOR = 0x02,
    FONT_PITCH_FAMILY_TT = 0x04,
    FONT_PITCH_FAMILY_DEVICE = 0x08,
}FontPitchAndFamily_e;

// Based on the TEXTMETRIC struct from windows 3.1
typedef struct TextMetrics{
    FontCharSet_e charSet;
    uint8_t height;
    uint8_t ascent;
    uint8_t descent;
    uint8_t internalLeading;
    uint8_t externalLeading;
    uint8_t avgCharWidth;
    uint8_t maxCharWidth;
    uint8_t weight;
    // RS_BOOL_e italic;
    // RS_BOOL_e underlined;
    // RS_BOOL_e struckOut;
    char firstChar;
    char lastChar;
    char defaultChar;
    char breakChar;
    uint8_t pitchAndFamily;
    // uint8_t overhang;
    uint8_t xDPI;
    uint8_t yDPI;
}TextMetrics_s;


#endif

