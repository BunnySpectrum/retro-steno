#include "alert.h"

void alert_error(){
    blink(BLINK_ERROR_COUNT, BLINK_ERROR_TIME);
}