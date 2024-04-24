#include "alert.h"

void alert_error(){
    blink(BLINK_ERROR_COUNT, BLINK_ERROR_TIME);
}

void print_build_time(void){
    printf(" \"build time\", \"value\": \"%s\"", __TIME__);

}