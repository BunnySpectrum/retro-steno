#include "hbt.h"

uint8_t hbtState;

void hbt_init(){
    hbtState = 0;
}

void hbt_toggle(){
    rs_gpio_put(LED_PIN, hbtState);
    hbtState ^= 0x1;
}