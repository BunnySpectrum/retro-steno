#include <stdio.h>

#include "unity.h"
#include "hw/drv_i2c.h"
#include "bsp/exp.h"
#include "utils/sys_time.h"


#include "tests/test_string.h"
#include "tests/test_ioexp.h"
#include "tests/test_modelpoint.h"
#include "tests/test_mp_keyboard.h"
#include "tests/test_keyboard.h"
#include "tests/test_gpio.h"
#include "tests/test_display.h"
#include "tests/test_sys_time.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}


// not needed when using generate_test_runner.rb
int main(void) {
    printf("Built %s\n", __TIME__);
    sys_time_init(0);

    UNITY_BEGIN();

    test_string();
    test_gpio();
    test_ioexp();
    test_modelpoint();    
    test_mp_keyboard();
    test_keyboard();
    test_display();
    test_sys_time();

    return UNITY_END();
}