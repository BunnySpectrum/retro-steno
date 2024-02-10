
#include <stdio.h>

#include "unity.h"
#include "hw/drv_i2c.h"
#include "bsp/exp.h"

void setup_test_ioexp(void) {
    // set stuff up here
}

void teardown_test_ioexp(void) {
    // clean stuff up here
}

void test_ioexp_check(void) {
    uint8_t data;

    TEST_ASSERT_EQUAL(RS_CODE_OK, exp_check(0, EXP_0));
    TEST_ASSERT_EQUAL(RS_CODE_OK, exp_check(0, EXP_1));
    TEST_ASSERT_EQUAL(RS_CODE_OK, exp_check(0, EXP_2));
    TEST_ASSERT_EQUAL(RS_CODE_OK, exp_check(0, EXP_3));
}

