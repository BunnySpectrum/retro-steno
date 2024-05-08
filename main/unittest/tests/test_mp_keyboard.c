// #include <stdio.h>
#include "utils/rs_stdio.h"

#include "unity.h"
#include "test_mp_keyboard.h"


    // uint16_t scratch16 = 0;
    // uint8_t dataSize = 4;
    // uint8_t subCount = 2;
    // uint16_t initSeq = 1;
    // mpSubscriber_t subList[] = {(mpSubscriber_t){.startSequence=2}, (mpSubscriber_t){.startSequence=3}}; 

    // mpBase_t mp;
    // mp.name = "test";




void test_mp_keyboard_init(void) {
    uint16_t scratch16 = 0;
    uint8_t dataSize = sizeof(MPKeyboardData_t);
    uint8_t subCount = 2;
    uint16_t initSeq = 1;
    mpSubscriber_t subList[] = {(mpSubscriber_t){.startSequence=2}, (mpSubscriber_t){.startSequence=3}}; 

    MPKeyboard_t kb;
    kb.base.name = "keyboard-init";

    // mp_print(mp);
    TEST_ASSERT(dataSize != kb.base.dataSize);
    TEST_ASSERT(subCount != kb.base.subscriberCount);
    TEST_ASSERT(initSeq != kb.base.sequence);
    TEST_ASSERT((mpSubscriber_t*)&subList != kb.base.subscribers);
    TEST_ASSERT_EQUAL_STRING("keyboard-init", kb.base.name);

    keyboard_mp_init(&kb, (mpSubscriber_t*)&subList, subCount);

    TEST_ASSERT(dataSize == kb.base.dataSize);
    TEST_ASSERT(subCount == kb.base.subscriberCount);
    TEST_ASSERT(initSeq == kb.base.sequence);
    TEST_ASSERT((mpSubscriber_t*)&subList == kb.base.subscribers);

    TEST_ASSERT_EQUAL_STRING("keyboard-init", mp_get_name(kb.base));

    TEST_ASSERT_EQUAL(initSeq, mp_get_sequence(kb.base));

    TEST_ASSERT_EQUAL(MP_INVALID, mp_is_valid(kb.base, &scratch16));
    TEST_ASSERT_EQUAL(scratch16, mp_get_sequence(kb.base));

    TEST_ASSERT_FALSE(mp_is_locked(kb.base));
    // mp_print(mp);
}

void test_mp_keyboard(){
    RUN_TEST(test_mp_keyboard_init);
}