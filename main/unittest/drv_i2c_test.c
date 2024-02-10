#include "hw/drv_i2c.h"


RSCode_e rs_i2c_init(uint8_t id, uint32_t speed){
    return RS_CODE_OK;
}

RSCode_e rs_i2c_read(uint8_t id, uint8_t addr, i2cResponse_t* resp, uint8_t nostop){
    resp->rc = RS_CODE_OK;

    switch(addr){
        case 0x38:
            resp->data[0] = 0;
            resp->length = 1;
            break;

        case 0x39:
            resp->data[0] = 0xFF;
            resp->length = 1;
            break;

        case 0x3A:
            resp->data[0] = 0xFF;
            resp->length = 1;
            break;

        case 0x3B:
            resp->data[0] = 0xFF;
            resp->length = 1;
            break;

        default:
            resp->rc = RS_CODE_ERR;
            break;
    }
    return resp->rc;
}
