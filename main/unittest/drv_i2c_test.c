#include "hw/drv_i2c.h"

#include <stdio.h>

uint8_t rs_i2c_init(uint8_t id, uint32_t speed){
    return 0;
}

uint8_t rs_i2c_read(uint8_t id, uint8_t addr, uint8_t *dst, size_t len, uint8_t nostop){
    uint8_t rc = 0;

    switch(addr){
        case 0x38:
            *dst = 0;
            rc = 1;
            break;

        case 0x39:
            *dst = 0xFF;
            rc = 1;
            break;

        case 0x3A:
            *dst = 0xFF;
            rc = 1;
            break;

        case 0x3B:
            *dst = 0xFF;
            rc = 1;
            break;

        default:
            rc = -2;
            break;
    }
    return rc;
}

uint8_t rs_i2c_info(uint8_t id){
    printf("In i2c_test driver: %d\n", id);
    return 0;
}