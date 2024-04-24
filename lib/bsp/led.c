#include "led.h"


void blink(uint8_t count, uint16_t delay){
    for(uint8_t i=0; i<count; i++){
        rs_gpio_put(LED_PIN, 1);
        rs_sleep_ms(delay);
        rs_gpio_put(LED_PIN, 0);
        rs_sleep_ms(delay);
    }
}