#include "utils/sys_time.h"

#include "pico/time.h"

uint32_t get_tick(){
    return to_ms_since_boot(get_absolute_time());
}

void rs_sleep_ms(uint32_t value){
    sleep_ms(value);
}
