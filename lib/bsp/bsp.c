#include "bsp.h"

#include "pico/stdio.h"
#include "pico/stdio_usb.h"

RS_CODE_e bsp_gpio_init(void (*gpio_callback)(unsigned int, uint32_t)){
    RS_GPIO_Config_s ledConfig = {
        .direction = RS_GPIO_OUTPUT,
        .function = RS_GPIO_FUNC_SIO,
        .value = 0
    };
    rs_gpio_init(LED_PIN, &ledConfig);

    RS_GPIO_Config_s enterKeyConfig = {
        .direction = RS_GPIO_INPUT,
        .function = RS_GPIO_FUNC_SIO,
        .value = 0
    };
    rs_gpio_init(PIN_KEY_ENTER, &enterKeyConfig);

    rs_gpio_set_input_hysteresis(PIN_KEY_ENTER, RS_TRUE);
    rs_gpio_set_irq_with_callback(PIN_KEY_ENTER, RS_GPIO_IRQ_EDGE_FALL, RS_TRUE, gpio_callback);

    return RS_CODE_OK;

}


RS_CODE_e bsp_usb_init(void (*char_callback)(void* data), uint64_t *cbTime){

    int flag = stdio_usb_init();
    stdio_set_chars_available_callback(char_callback, cbTime);

    if(flag == 0){
        // failed to setup CDC
        alert_error();
        return RS_CODE_ERR;
    }

    return RS_CODE_OK;

}

RS_CODE_e bsp_i2c_init(uint32_t i2cID){
    if(rs_i2c_init(i2cID, 100 * 1000) != RS_CODE_OK){
        printf("Error enabling i2c %d", I2C_ID);
        alert_error();
    };

    rs_gpio_set_function(SDA_PIN, RS_GPIO_FUNC_I2C);
    rs_gpio_set_function(SCL_PIN, RS_GPIO_FUNC_I2C);
    rs_gpio_pull_up(SDA_PIN);
    rs_gpio_pull_up(SCL_PIN);

}