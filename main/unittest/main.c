#include <stdio.h>

#include "unity.h"
#include "hw/drv_i2c.h"
#include "bsp/exp.h"


#include "tests/test_ioexp.h"
#include "tests/test_modelpoint.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}


// not needed when using generate_test_runner.rb
int main(void) {
    printf("Built %s\n", __TIME__);
    rs_i2c_info(0);

    UNITY_BEGIN();
    RUN_TEST(test_ioexp_check_0);
    RUN_TEST(test_ioexp_check_1);
    RUN_TEST(test_ioexp_check_2);
    RUN_TEST(test_ioexp_check_3);

    RUN_TEST(test_modelpoint_init);

    return UNITY_END();
}