// #include <stdio.h>
#include "utils/rs_stdio.h"

#include "unity.h"
#include "test_display.h"
#include "bsp/display.h"


void test_display_draw_pixel_invalid(void) {   
    RS_CODE_e result;

    display_init(); 
    result = display_draw_pixel(3, 0, 0, RS_RGB565_BLACK);
    TEST_ASSERT_EQUAL(RS_CODE_ERR, result);
    
}