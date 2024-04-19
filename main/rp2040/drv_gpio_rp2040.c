#include "hw/drv_gpio.h"

// use pico SDK as-is for now
#include "hardware/gpio.h"

RSCode_e rs_gpio_init(uint32_t id, const RS_GPIO_Config_s *cfg){
    if(cfg == NULL){
        gpio_init(id);
    }else{
        gpio_set_dir(id, cfg->direction);
        gpio_put(id, cfg->value);
        gpio_set_function(id, cfg->function);
    }
    return RS_CODE_OK;
}


RSCode_e rs_gpio_set_direction(uint32_t id, RS_GPIO_DIR_e val){
    gpio_set_dir(id, val);
    return RS_CODE_OK;
}

// True to set, False to clear
RSCode_e rs_gpio_put(uint32_t id, RS_BOOL_e val){
    gpio_put(id, val);
    return RS_CODE_OK;
}

// opaque value type to pass to HAL
RSCode_e rs_gpio_set_function(uint32_t id, uint32_t val){
    gpio_set_function(id, val);
    return RS_CODE_OK;
}

RSCode_e rs_gpio_set_input_hysteresis(uint32_t id, RS_BOOL_e val){
    gpio_set_input_hysteresis_enabled(id, val);
    return RS_CODE_OK;
}

RSCode_e rs_gpio_set_irq_with_callback(uint32_t id, uint32_t eventMask, RS_BOOL_e enable, void (*callback)(unsigned int id, uint32_t eventMask)){
    gpio_set_irq_enabled_with_callback(id, eventMask, enable, callback);
    return RS_CODE_OK;
}

RSCode_e rs_gpio_pull_up(uint32_t id){
    gpio_pull_up(id);
    return RS_CODE_OK;
}

RSCode_e rs_gpio_pull_down(uint32_t id){
    gpio_pull_down(id);
    return RS_CODE_OK;
}