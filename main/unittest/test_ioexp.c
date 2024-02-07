#include <stdio.h>

#include "unity.h"
#include "hw/drv_i2c.h"
#include "bsp/exp.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
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

// not needed when using generate_test_runner.rb
int main(void) {
    printf("Built %s\n", __TIME__);
    UNITY_BEGIN();
    RUN_TEST(test_ioexp_check_0);
    RUN_TEST(test_ioexp_check_1);
    RUN_TEST(test_ioexp_check_2);
    RUN_TEST(test_ioexp_check_3);
    return UNITY_END();
}