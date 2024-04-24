#include "rs_time.h"

void print_timestamp(uint64_t timestamp){
    uint64_t sec, msec, usec;

    sec = timestamp/1e6;
    msec = (timestamp/1e3) - sec*1e3;
    usec = timestamp- sec*1e6 - msec*1e3;

    printf("Time (s, ms, us): %lld, %lld, %lld\n", sec, msec, usec);
    return;
}