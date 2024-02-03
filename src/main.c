//#include <stdint.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define BLINK_LONG 500
#define BLINK_HBT 10
#define BLINK_FAST 100

#define LED_PIN 13
#define SDA_PIN 16
#define SCL_PIN 17

// I2C reserves some addresses for special purposes. We exclude these from the scan.
// These are any addresses of the form 000 0xxx or 111 1xxx
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

void blink(uint8_t count, uint16_t delay){
    for(uint8_t i=0; i<count; i++){
        gpio_put(LED_PIN, 1);
        sleep_ms(delay);
        gpio_put(LED_PIN, 0);
        sleep_ms(delay);
    }

}


void bus_scan(i2c_inst_t* i2c){
    printf("\nV2 I2C Bus Scan\n");
    printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

    for (int addr = 0; addr < (1 << 7); ++addr) {
        if (addr % 16 == 0) {
            printf("%02x ", addr);
        }

        // Perform a 1-byte dummy read from the probe address. If a slave
        // acknowledges this address, the function returns the number of bytes
        // transferred. If the address byte is ignored, the function returns
        // -1.

        // Skip over any reserved addresses.
        int ret;
        uint8_t rxdata;
        if (reserved_addr(addr))
            ret = PICO_ERROR_GENERIC;
        else
            ret = i2c_read_blocking(i2c, addr, &rxdata, 1, false);

        printf(ret < 0 ? "." : "@");
        printf(addr % 16 == 15 ? "\n" : "  ");
    }
    printf("Done.\n");

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

#if !defined(i2c_default) || !defined(SDA_PIN) || !defined(SCL_PIN)
#warning i2c/bus_scan example requires a board with I2C pins
    puts("Default I2C pins were not defined");
#else
#endif

    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(SDA_PIN, SCL_PIN, GPIO_FUNC_I2C));


    bus_scan(i2c_default);


    while (true) {
        value = getchar();
        //printf("Got %c\n", value);
        blink(1, BLINK_HBT);

        if(value == 's')
            bus_scan(i2c_default);
        else if(value == 'r'){
            printf("Read\n");
            i2c_read_blocking(i2c_default, 0x38, &value, 1, 0);
            printf("  Got %x\n", value);
        }
    }
}
