#include "hw/drv_i2c.h"

//pico SDK
#include "hardware/i2c.h"



#define I2C_INSTANCE_COUNT 2
static i2c_inst_t *i2c_instances[I2C_INSTANCE_COUNT] = {&i2c0_inst, &i2c1_inst};

RS_CODE_e rs_i2c_init(uint8_t id, uint32_t speed){
    uint32_t actualSpeed;

    if (id > I2C_INSTANCE_COUNT-1){
        return RS_CODE_ERR;
    }

    actualSpeed = i2c_init(i2c_instances[id], speed);
    if (actualSpeed == speed){
        return RS_CODE_OK;
    }

    return RS_CODE_ERR;

}

RS_CODE_e rs_i2c_read(uint8_t id, uint8_t addr, i2cResponse_t* resp, uint8_t nostop){
    resp->rc = RS_CODE_ERR;

    if (id > I2C_INSTANCE_COUNT-1){
        return resp->rc;
    }
        
    if(resp->length == i2c_read_blocking(i2c_instances[id], addr, resp->data, resp->length, nostop)){
        resp->rc = RS_CODE_OK;
    }

    return resp->rc;

}
