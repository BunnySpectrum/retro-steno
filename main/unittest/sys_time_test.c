#include "utils/sys_time.h"

#include "time.h"

static uint64_t currentTimeTick;

uint64_t get_tick(){
    return currentTimeTick;
}

static clock_t rs_now_ms(){
    clock_t result;
    
    result = (clock() / CLOCKS_PER_SEC)*1000;

    return result;
}

// c.f. https://www.geeksforgeeks.org/time-delay-c/
void rs_sleep_ms(uint32_t value){
    sys_time_init(get_tick() + (uint64_t)value * 1000);
    // clock_t start = rs_now_ms();

    // while((start + value) > rs_now_ms()){
    //     ;
    // }
}

RS_CODE_e sys_time_init(uint64_t val){
    currentTimeTick = val;
    return RS_CODE_OK;
}