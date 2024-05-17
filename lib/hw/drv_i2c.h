#ifndef _DRV_I2C_H_
#define _DRV_I2C_H_

#include "utils/rs_stdint.h"
#include "utils/rs_stddef.h"
#include "utils/rs_codes.h"

typedef struct i2cResponse{
    RS_CODE_e rc;
    uint8_t* data;
    size_t length;

} i2cResponse_t;


RS_CODE_e rs_i2c_init(uint8_t id, uint32_t speed);

RS_CODE_e rs_i2c_read(uint8_t id, uint8_t addr, i2cResponse_t* resp, uint8_t nostop);

RS_CODE_e rs_i2c_write(uint8_t id, uint8_t addr, i2cResponse_t* resp, uint8_t nostop);




#endif