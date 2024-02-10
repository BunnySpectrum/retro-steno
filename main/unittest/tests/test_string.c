// #include <stdio.h>
#include "utils/rs_string.h"
#include "utils/rs_stdio.h"


#include "unity.h"
#include "test_string.h"


void setup_test_string(void) {
    // set stuff up here
}

void teardown_test_string(void) {
    // clean stuff up here
}


void test_strcpy(void){
    char str1[] = "alpha";
    char str2[] = "1234";
    char str3[] = "";

    rs_strcpy(str1, str2);
    TEST_ASSERT_EQUAL_STRING(str1, str2);
    
    rs_strcpy(str1, str3);
    TEST_ASSERT_EQUAL_STRING(str1, str3);
}

void test_strlen(void){
    // char* str1 = "alpha";
    char str1[] = "alpha";
    char str2[] = "";
    char str3[] = "a";

    TEST_ASSERT_EQUAL(5, rs_strlen(str1));
    TEST_ASSERT_EQUAL(0, rs_strlen(str2));
    TEST_ASSERT_EQUAL(1, rs_strlen(str3));
}