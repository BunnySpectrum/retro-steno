#ifndef _DRV_I2C_H_
#define _DRV_I2C_H_

#include <stdlib.h>
#include <stdint.h>

// typedef struct i2c_instance i2c_instance_t;
// struct i2c_instance{
//     void *mem_struct;
//     void *option_struct;
// };

// extern i2c_instance_t i2c0_instance;
// extern i2c_instance_t i2c1_instance;

uint8_t rs_i2c_init(uint8_t id, uint32_t speed);

uint8_t rs_i2c_read(uint8_t id, uint8_t addr, uint8_t *dst, size_t len, uint8_t nostop);

uint8_t rs_i2c_info(uint8_t id);



#endif