#include "utils/rs_colors.h"

RS_CODE_e rgb565_for_index(uint8_t idx, RS_RGB565_e *color){
    if(idx >= RGB565_COLOR_COUNT){
        return RS_CODE_ERR;
    }

    *color = rgb565List[idx];

    return RS_CODE_OK;
}