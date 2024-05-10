
#include <stdio.h>

#include "unity.h"
#include "hw/drv_gpio.h"

extern RS_BOOL_e TEST_GPIO_VALUE[];
extern RS_GPIO_DIR_e TEST_GPIO_DIR[];
extern RS_GPIO_FUNC_e TEST_GPIO_FUNC[];
extern RS_GPIO_IRQ_e TEST_GPIO_IRQ[];




void assert_gpio_state(uint32_t id, RS_GPIO_DIR_e dir, RS_GPIO_FUNC_e func, RS_BOOL_e val){
    TEST_ASSERT_EQUAL(dir, (RS_GPIO_DIR_e)TEST_GPIO_DIR[id]);
    TEST_ASSERT_EQUAL(func, (RS_GPIO_FUNC_e)TEST_GPIO_FUNC[id]);
    TEST_ASSERT_EQUAL(val, (RS_BOOL_e)TEST_GPIO_VALUE[id]);
}

void test_gpio_init_null(void) {
    uint32_t gpioID = 1;

    assert_gpio_state(gpioID, 0, 0, 0);
    TEST_ASSERT_EQUAL(RS_CODE_OK, rs_gpio_init(gpioID, NULL));
    assert_gpio_state(gpioID, RS_GPIO_INPUT, RS_GPIO_FUNC_SIO, 0);
}




void test_gpio_init_cfg(void) {
    uint32_t gpioID = 2;

    RS_GPIO_Config_s cfg = {
        .direction = RS_GPIO_OUTPUT,
        .function = RS_GPIO_FUNC_I2C,
        .value = RS_TRUE
    };

    assert_gpio_state(gpioID, 0, 0, 0);
    TEST_ASSERT_EQUAL(RS_CODE_OK, rs_gpio_init(gpioID, &cfg));
    assert_gpio_state(gpioID, RS_GPIO_OUTPUT, RS_GPIO_FUNC_I2C, RS_TRUE);
}

void test_gpio(void){
    RUN_TEST(test_gpio_init_null);
    RUN_TEST(test_gpio_init_cfg);
}