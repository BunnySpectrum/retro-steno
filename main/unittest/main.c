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

    RUN_TEST(test_gpio_init_null);
    RUN_TEST(test_gpio_init_cfg);

    RUN_TEST(test_ioexp_check);
    RUN_TEST(test_ioexp_read);

    RUN_TEST(test_modelpoint_init);
    RUN_TEST(test_modelpoint_set_lock_state);
    RUN_TEST(test_modelpoint_set_invalid);
    
    RUN_TEST(test_mp_keyboard_init);
    RUN_TEST(test_print_keyboard_state);

    RUN_TEST(test_display_draw_pixel_invalid);

    printf("Tick\n");
    rs_sleep_ms(1000);
    printf("Tock\n");
    rs_sleep_ms(1000);
    printf("Tick\n");
    rs_sleep_ms(1000);
    printf("Tock\n");
    rs_sleep_ms(1000);

    return UNITY_END();
}