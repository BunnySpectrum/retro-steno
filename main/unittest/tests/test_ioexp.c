
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

void test_ioexp_check_0(void) {
    uint8_t data;

    TEST_ASSERT(1 == exp_check(0, EXP_0));
}

void test_ioexp_check_1(void) {
    uint8_t data;

    TEST_ASSERT(1 == exp_check(0, EXP_1));
}

void test_ioexp_check_2(void) {
    uint8_t data;

    TEST_ASSERT(1 == exp_check(0, EXP_2));
}

void test_ioexp_check_3(void) {
    uint8_t data;

    TEST_ASSERT(1 == exp_check(0, EXP_3));
}
