#include "bsp.h"

#include "pico/stdio.h"
#include "pico/stdio_usb.h"
#include "hardware/pwm.h"

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

    if(i2cID == 0){
        rs_gpio_set_function(SDA_PIN, RS_GPIO_FUNC_I2C);
        rs_gpio_set_function(SCL_PIN, RS_GPIO_FUNC_I2C);
        rs_gpio_pull_up(SDA_PIN);
        rs_gpio_pull_up(SCL_PIN);
    }else{
        rs_gpio_set_function(10, RS_GPIO_FUNC_I2C);
        rs_gpio_set_function(11, RS_GPIO_FUNC_I2C);
        rs_gpio_pull_up(10);
        rs_gpio_pull_up(11);

    }

    return RS_CODE_OK;
}

RS_BOOL_e bsp_spi_init(uint32_t spiID){
    rs_spi_init(spiID, 4000*1000); // 4 MHz clock
    rs_gpio_set_function(SPI_DISP_SCK_PIN, RS_GPIO_FUNC_SPI);
    rs_gpio_set_function(SPI_DISP_MOSI_PIN, RS_GPIO_FUNC_SPI);
    rs_gpio_set_function(SPI_DISP_MISO_PIN, RS_GPIO_FUNC_SPI);
    // rs_gpio_set_function(SPI_DISP_CS_PIN, RS_GPIO_FUNC_SPI);

    rs_gpio_init(SPI_DISP0_CS_PIN, NULL);
    rs_gpio_set_direction(SPI_DISP0_CS_PIN, RS_GPIO_OUTPUT);
    rs_gpio_put(SPI_DISP0_CS_PIN, 1);

    rs_gpio_init(SPI_DISP1_CS_PIN, NULL);
    rs_gpio_set_direction(SPI_DISP1_CS_PIN, RS_GPIO_OUTPUT);
    rs_gpio_put(SPI_DISP1_CS_PIN, 1);


    rs_gpio_init(SPI_DISP0_CARD_CS_PIN, NULL);
    rs_gpio_set_direction(SPI_DISP0_CARD_CS_PIN, RS_GPIO_OUTPUT);
    rs_gpio_put(SPI_DISP0_CARD_CS_PIN, 1);
    
    rs_gpio_init(SPI_DISP1_CARD_CS_PIN, NULL);
    rs_gpio_set_direction(SPI_DISP1_CARD_CS_PIN, RS_GPIO_OUTPUT);
    rs_gpio_put(SPI_DISP1_CARD_CS_PIN, 1);

    spiResponse_t resp;
    rs_spi_mode(&resp, spiID, 8, RS_FALSE, RS_FALSE, RS_TRUE);



    return RS_CODE_OK;
}

RS_BOOL_e bsp_display_init(){
    rs_gpio_init(DISP0_RST_PIN, NULL);
    rs_gpio_set_direction(DISP0_RST_PIN, RS_GPIO_OUTPUT);
    rs_gpio_put(DISP0_RST_PIN, 1);
    
    rs_gpio_init(DISP1_RST_PIN, NULL);
    rs_gpio_set_direction(DISP1_RST_PIN, RS_GPIO_OUTPUT);
    rs_gpio_put(DISP1_RST_PIN, 1);



    rs_gpio_init(DISP0_DC_PIN, NULL);
    rs_gpio_set_direction(DISP0_DC_PIN, RS_GPIO_OUTPUT);
    rs_gpio_put(DISP0_DC_PIN, 0);
    
    rs_gpio_init(DISP1_DC_PIN, NULL);
    rs_gpio_set_direction(DISP1_DC_PIN, RS_GPIO_OUTPUT);
    rs_gpio_put(DISP1_DC_PIN, 0);
    


    unsigned int sliceNum;

    rs_gpio_set_function(DISP0_LIGHT_PIN, RS_GPIO_FUNC_PWM);
    sliceNum = pwm_gpio_to_slice_num(DISP0_LIGHT_PIN);
    pwm_set_wrap(sliceNum, 12500);
    pwm_set_gpio_level(DISP0_LIGHT_PIN, 3125*2);
    pwm_set_enabled(sliceNum, 1);

    rs_gpio_set_function(DISP1_LIGHT_PIN, RS_GPIO_FUNC_PWM);
    sliceNum = pwm_gpio_to_slice_num(DISP1_LIGHT_PIN);
    pwm_set_wrap(sliceNum, 12500);
    pwm_set_gpio_level(DISP1_LIGHT_PIN, 3125*2);
    pwm_set_enabled(sliceNum, 1);

}