#include "hw/drv_gpio.h"

#include <stdio.h>

RS_CODE_e rs_gpio_init(uint32_t id, const RS_GPIO_Config_s *cfg){
    if(cfg == NULL){
        printf("Init gpio %d: default\n", id);
    }else{
        printf("Init gpio %d: dir %d, value %d, function %d\n", id, cfg->direction, cfg->value, cfg->value);
    }
    return RS_CODE_OK;
}


RS_CODE_e rs_gpio_set_direction(uint32_t id, RS_GPIO_DIR_e val){
    printf("Set dir gpio %d: %d\n", id, val);
    return RS_CODE_OK;
}

// True to set, False to clear
RS_CODE_e rs_gpio_put(uint32_t id, RS_BOOL_e val){
    printf("Put gpio %d: %d\n", id, val);
    return RS_CODE_OK;
}

// opaque value type to pass to HAL
RS_CODE_e rs_gpio_set_function(uint32_t id, uint32_t val){
    printf("Set function gpio %d: %d\n", id, val);
    return RS_CODE_OK;
}

RS_CODE_e rs_gpio_set_input_hysteresis(uint32_t id, RS_BOOL_e val){
    printf("Set input hyst gpio %d: %d\n", id, val);
    return RS_CODE_OK;
}

RS_CODE_e rs_gpio_set_irq_with_callback(uint32_t id, uint32_t eventMask, RS_BOOL_e enable, void (*callback)(unsigned int id, uint32_t eventMask)){
    printf("Set irq w/ callback gpio %d: %d, %p\n", id, enable, callback);
    return RS_CODE_OK;
}

RS_CODE_e rs_gpio_pull_up(uint32_t id){
    printf("Pull up gpio %d\n", id);
    return RS_CODE_OK;
}

RS_CODE_e rs_gpio_pull_down(uint32_t id){
    printf("Pull down gpio %d\n", id);
    return RS_CODE_OK;
}