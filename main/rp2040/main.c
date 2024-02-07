//#include <stdint.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "pico/binary_info.h"

#include "bsp/exp.h"
#include "hw/drv_i2c.h"

#define BLINK_LONG 500
#define BLINK_HBT 10
#define BLINK_FAST 100

#define LED_PIN 13
#define SDA_PIN 16
#define SCL_PIN 17

#define I2C_ID 0


void blink(uint8_t count, uint16_t delay){
    for(uint8_t i=0; i<count; i++){
        gpio_put(LED_PIN, 1);
        sleep_ms(delay);
        gpio_put(LED_PIN, 0);
        sleep_ms(delay);
    }
}



int main() {

    uint8_t flag = 0;
    uint8_t value = 0;


    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    flag = stdio_usb_init();

    if(flag == 0){
        // failed to setup CDC
        blink(2, BLINK_FAST);
    }else{
        // success
        blink(5, BLINK_FAST);
    }

    rs_i2c_init(I2C_ID, 100 * 1000);

    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(SDA_PIN, SCL_PIN, GPIO_FUNC_I2C));

    printf("Starting.\n");
    while (true) {
        value = getchar();
        //printf("Got %c\n", value);
        blink(1, BLINK_HBT);

        switch(value){
            case 'i':
                printf("Built at %s\n", __TIME__);
                break;
            case 's':
                exp_search(I2C_ID);
                break;
            case '\n':
                printf("\n");
                break;
            case '\r':
                printf("\r");
                break;
            case 'r':
                printf("Read\n");
                if (rs_i2c_read(I2C_ID, 0x37, &value, 1, 0) < 0){
                    printf("err addr %x\n", 0x37);
                }else{
                    printf("  Read %x\n", value);
                }
                break;
            case 'c':
                printf("Addr %#x: %d\n", EXP_0, exp_check(I2C_ID, EXP_0));
                printf("Addr %#x: %d\n", EXP_1, exp_check(I2C_ID, EXP_1));
                printf("Addr %#x: %d\n", EXP_2, exp_check(I2C_ID, EXP_2));
                printf("Addr %#x: %d\n", EXP_3, exp_check(I2C_ID, EXP_3));
                break;
            case '0':
                if (rs_i2c_read(I2C_ID, EXP_0, &value, 1, 0) < 0){
                    printf("err addr %x\n", EXP_0);
                }else{
                    printf("%#x: %#x\n", EXP_0, value);
                }
                break;
            case '1':
                if (rs_i2c_read(I2C_ID, EXP_1, &value, 1, 0) < 0){
                    printf("err addr %x\n", EXP_1);
                }else{
                    printf("%#x: %#x\n", EXP_1, value);
                }
                break;
            case '2':
                if (rs_i2c_read(I2C_ID, EXP_2, &value, 1, 0) < 0){
                    printf("err addr %x\n", EXP_2);
                }else{
                    printf("%#x: %#x\n", EXP_2, value);
                }
                break;
            case '3':
                if (rs_i2c_read(I2C_ID, EXP_3, &value, 1, 0) < 0){
                    printf("err addr %x\n", EXP_3);
                }else{
                    printf("%#x: %#x\n", EXP_3, value);
                }
                break;
            default:
                // printf("\t%#x\n", value);
                break;

        }
    }
}
