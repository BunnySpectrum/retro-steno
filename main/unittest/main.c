#include <stdio.h>

#include "unity.h"
#include "hw/drv_i2c.h"
#include "bsp/exp.h"


#include "tests/test_string.h"
#include "tests/test_ioexp.h"
#include "tests/test_modelpoint.h"
#include "tests/test_mp_keyboard.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}


// not needed when using generate_test_runner.rb
int main(void) {
    printf("Built %s\n", __TIME__);

    UNITY_BEGIN();
    RUN_TEST(test_strcpy);
    RUN_TEST(test_strlen);

    RUN_TEST(test_ioexp_check);

    RUN_TEST(test_modelpoint_init);
    RUN_TEST(test_modelpoint_set_lock_state);
    RUN_TEST(test_modelpoint_set_invalid);
    
    RUN_TEST(test_mp_keyboard_init);

    return UNITY_END();
}