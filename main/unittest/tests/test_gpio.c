
#include <stdio.h>

#include "unity.h"
#include "hw/drv_gpio.h"


void test_gpio_init_null(void) {
    TEST_ASSERT_EQUAL(RS_CODE_OK, rs_gpio_init(1, NULL));
}

void test_gpio_init_cfg(void) {
    RS_GPIO_Config_s cfg = {
        .direction = RS_GPIO_OUTPUT,
        .function = 1,
        .value = 1
    };

    TEST_ASSERT_EQUAL(RS_CODE_OK, rs_gpio_init(2, &cfg));
}
