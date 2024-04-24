#include "utils/rs_stdio.h"

#include "pico/stdio.h"


RS_CODE_e rs_getchar_timeout_us(uint32_t timeout, int *val){
    int result = getchar_timeout_us(timeout);
    if(result == PICO_ERROR_TIMEOUT){
        return RS_CODE_ERR;
    }

    *val = result;
    return RS_CODE_OK;
}