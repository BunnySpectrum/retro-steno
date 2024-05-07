#include "utils/sys_time.h"

#include "pico/time.h"

uint64_t get_tick(){
    return to_ms_since_boot(get_absolute_time());
}

void rs_sleep_ms(uint32_t value){
    sleep_ms(value);
}

RS_CODE_e sys_time_init(uint64_t val){
    // taken care of by rp2040 SDK 
    return RS_CODE_OK;
}