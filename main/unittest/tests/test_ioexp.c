
#include <stdio.h>

#include "unity.h"
#include "hw/drv_i2c.h"
#include "bsp/exp.h"


void test_ioexp_check(void) {
    uint8_t data;

    TEST_ASSERT_EQUAL(RS_CODE_OK, exp_check(0, EXP_0));
    TEST_ASSERT_EQUAL(RS_CODE_OK, exp_check(0, EXP_1));
    TEST_ASSERT_EQUAL(RS_CODE_OK, exp_check(0, EXP_2));
    TEST_ASSERT_EQUAL(RS_CODE_OK, exp_check(0, EXP_3));
}

void test_ioexp_read(void) {
    uint8_t data;
    i2cResponse_t i2cResp;
    i2cResp.length = 1;
    i2cResp.data = &data;

    TEST_ASSERT_EQUAL(RS_CODE_OK, rs_i2c_read(0, EXP_0, &i2cResp, 0));
    TEST_ASSERT_EQUAL(0x00, *i2cResp.data);
    
    TEST_ASSERT_EQUAL(RS_CODE_OK, rs_i2c_read(0, EXP_1, &i2cResp, 0));
    TEST_ASSERT_EQUAL(0xFF, *i2cResp.data);
    
    TEST_ASSERT_EQUAL(RS_CODE_OK, rs_i2c_read(0, EXP_2, &i2cResp, 0));
    TEST_ASSERT_EQUAL(0xFF, *i2cResp.data);
    
    TEST_ASSERT_EQUAL(RS_CODE_OK, rs_i2c_read(0, EXP_3, &i2cResp, 0));
    TEST_ASSERT_EQUAL(0xFF, *i2cResp.data);
}

void test_ioexp(void){
    RUN_TEST(test_ioexp_check);
    RUN_TEST(test_ioexp_read);
}