// #include <stdio.h>
#include "utils/rs_stdio.h"

#include "unity.h"
#include "test_sys_time.h"
#include "utils/sys_time.h"


void test_sys_time_get_tick(void) {   

    sys_time_init(0);
    TEST_ASSERT_EQUAL(0, get_tick());

    sys_time_init(10);
    TEST_ASSERT_EQUAL(10, get_tick());
}

void test_sys_time_rs_sleep(void) {   

    sys_time_init(0);
    TEST_ASSERT_GREATER_OR_EQUAL(0, get_tick());

    rs_sleep_ms(32);
    TEST_ASSERT_GREATER_OR_EQUAL(32*1000, get_tick());
}

void test_sys_time(void){
    RUN_TEST(test_sys_time_get_tick);
    RUN_TEST(test_sys_time_rs_sleep);
}