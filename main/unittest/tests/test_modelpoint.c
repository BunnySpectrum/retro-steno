// #include <stdio.h>
#include "utils/rs_stdio.h"

#include "unity.h"
#include "test_modelpoint.h"

#include "app/model_point.h"

    // uint16_t scratch16 = 0;
    // uint8_t dataSize = 4;
    // uint8_t subCount = 2;
    // uint16_t initSeq = 1;
    // mpSubscriber_t subList[] = {(mpSubscriber_t){.startSequence=2}, (mpSubscriber_t){.startSequence=3}}; 

    // mpBase_t mp;
    // mp.name = "test";

void setup_test_modelpoint(void) {
    // set stuff up here
}

void teardown_test_modelpoint(void) {
    // clean stuff up here
}


void test_modelpoint_init(void) {
    uint16_t scratch16 = 0;
    uint8_t dataSize = 4;
    uint8_t subCount = 2;
    uint16_t initSeq = 1;
    mpSubscriber_t subList[] = {(mpSubscriber_t){.startSequence=2}, (mpSubscriber_t){.startSequence=3}}; 

    mpBase_t mp;
    mp.name = "test";

    // mp_print(mp);
    TEST_ASSERT(dataSize != mp.dataSize);
    TEST_ASSERT(subCount != mp.subscriberCount);
    TEST_ASSERT(initSeq != mp.sequence);
    TEST_ASSERT((mpSubscriber_t*)&subList != mp.subscribers);
    TEST_ASSERT_EQUAL_STRING("test", mp.name);

    mp_init(&mp, (mpSubscriber_t*)&subList, subCount, dataSize);

    TEST_ASSERT(dataSize == mp.dataSize);
    TEST_ASSERT(subCount == mp.subscriberCount);
    TEST_ASSERT(initSeq == mp.sequence);
    TEST_ASSERT((mpSubscriber_t*)&subList == mp.subscribers);

    TEST_ASSERT_EQUAL_STRING("test", mp_get_name(mp));

    TEST_ASSERT_EQUAL(initSeq, mp_get_sequence(mp));

    TEST_ASSERT_EQUAL(MP_INVALID, mp_is_valid(mp, &scratch16));
    TEST_ASSERT_EQUAL(scratch16, mp_get_sequence(mp));

    TEST_ASSERT_FALSE(mp_is_locked(mp));
    // mp_print(mp);
}

void test_modelpoint_set_lock_state(void){
    uint16_t scratch16 = 0;
    uint8_t dataSize = 4;
    uint8_t subCount = 2;
    uint16_t initSeq = 1;
    mpSubscriber_t subList[] = {(mpSubscriber_t){.startSequence=2}, (mpSubscriber_t){.startSequence=3}}; 

    mpBase_t mp;
    mp.name = "set-lock-state";
    mp_init(&mp, (mpSubscriber_t*)&subList, subCount, dataSize);

    // Confirm initially unlocked and seq=1
    TEST_ASSERT_FALSE(mp_is_locked(mp));
    TEST_ASSERT_EQUAL(1, mp_get_sequence(mp));

    // Confirm now locked and we returned the seq
    scratch16 = mp_set_lock_state(&mp, mpLockReqLock);
    TEST_ASSERT_EQUAL(1, scratch16);
    TEST_ASSERT_EQUAL(MP_TRUE, mp_is_locked(mp));
    
    // Confirm still locked
    scratch16 = mp_set_lock_state(&mp, mpLockReqNone);
    TEST_ASSERT_EQUAL(1, scratch16);
    TEST_ASSERT_EQUAL(MP_TRUE, mp_is_locked(mp));

    // Confirm unlocked
    scratch16 = mp_set_lock_state(&mp, mpLockReqUnlock);
    TEST_ASSERT_EQUAL(1, scratch16);
    TEST_ASSERT_EQUAL(MP_FALSE, mp_is_locked(mp));


    // Confirm stil unlocked
    scratch16 = mp_set_lock_state(&mp, mpLockReqNone);
    TEST_ASSERT_EQUAL(1, scratch16);
    TEST_ASSERT_EQUAL(MP_FALSE, mp_is_locked(mp));

}

void test_modelpoint_set_invalid(void){
    uint16_t scratch16 = 0;
    uint8_t dataSize = 4;
    uint8_t subCount = 2;
    uint16_t initSeq = 1;
    mpSubscriber_t subList[] = {(mpSubscriber_t){.startSequence=2}, (mpSubscriber_t){.startSequence=3}}; 

    mpBase_t mp;
    mp.name = "set-invalid";
    mp_init(&mp, (mpSubscriber_t*)&subList, subCount, dataSize);
    TEST_ASSERT_EQUAL(initSeq, mp_get_sequence(mp));
    TEST_ASSERT_EQUAL(MP_FALSE, mp_is_locked(mp));

    // Confirm initially invalid and seq=1
    TEST_ASSERT_EQUAL(MP_INVALID, mp_is_valid(mp, &scratch16));
    TEST_ASSERT_EQUAL(initSeq, scratch16);

    // Confirm now valid and we returned the seq
    mp.valid = MP_VALID;
    TEST_ASSERT_EQUAL(MP_VALID, mp_is_valid(mp, &scratch16));
    TEST_ASSERT_EQUAL(initSeq, scratch16);
    
    // Set to invalid
    scratch16 = mp_set_invalid(&mp, mpLockReqLock);
    TEST_ASSERT_EQUAL(initSeq, scratch16);
    TEST_ASSERT_EQUAL(MP_TRUE, mp_is_locked(mp));


    scratch16 = mp_set_invalid(&mp, mpLockReqNone);
    TEST_ASSERT_EQUAL(initSeq, scratch16);
    TEST_ASSERT_EQUAL(MP_TRUE, mp_is_locked(mp));

    scratch16 = mp_set_invalid(&mp, mpLockReqUnlock);
    TEST_ASSERT_EQUAL(initSeq, scratch16);
    TEST_ASSERT_EQUAL(MP_FALSE, mp_is_locked(mp));
    
    scratch16 = mp_set_invalid(&mp, mpLockReqNone);
    TEST_ASSERT_EQUAL(initSeq, scratch16);
    TEST_ASSERT_EQUAL(MP_FALSE, mp_is_locked(mp));
}



