#include "hw/drv_i2c.h"

//pico SDK
#include "hardware/i2c.h"

#include <stdio.h>

#define I2C_INSTANCE_COUNT 2
static i2c_inst_t *i2c_instances[I2C_INSTANCE_COUNT] = {&i2c0_inst, &i2c1_inst};

uint8_t rs_i2c_init(uint8_t id, uint32_t speed){
    if (id > I2C_INSTANCE_COUNT-1){
        return PICO_ERROR_GENERIC;
    }

    i2c_init(i2c_instances[id], speed);

}

uint8_t rs_i2c_read(uint8_t id, uint8_t addr, uint8_t *dst, size_t len, uint8_t nostop){
    if (id > I2C_INSTANCE_COUNT-1){
        return PICO_ERROR_GENERIC;
    }
        
    return i2c_read_blocking(i2c_instances[id], addr, dst, len, nostop);

}

uint8_t rs_i2c_info(uint8_t id){
    printf("In i2c_rp2040 driver: %d\n", id);
    return 0;
}