#include "utils/sys_time.h"

#include "time.h"

uint32_t get_tick(){
    return 1;
}

static clock_t rs_now_ms(){
    clock_t result;
    
    result = (clock() / CLOCKS_PER_SEC)*1000;

    return result;
}

// c.f. https://www.geeksforgeeks.org/time-delay-c/
void rs_sleep_ms(uint32_t value){
    clock_t start = rs_now_ms();

    while((start + value) > rs_now_ms()){
        ;
    }
}
