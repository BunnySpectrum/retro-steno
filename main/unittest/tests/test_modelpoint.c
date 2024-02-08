#include <stdio.h>

#include "unity.h"
#include "test_modelpoint.h"

#include "app/model_point.h"

void setup_test_modelpoint(void) {
    // set stuff up here
}

void teardown_test_modelpoint(void) {
    // clean stuff up here
}


void test_modelpoint_init(void) {
    uint8_t dataSize = 4;
    uint8_t subCount = 2;
    uint16_t initSeq = 1;
    mpSubscriber_t subList[] = {(mpSubscriber_t){.startSequence=2}, (mpSubscriber_t){.startSequence=3}}; 

    mpBase_t mp;
    mp.name = "test";
    mp_print(mp);
    TEST_ASSERT(dataSize != mp.dataSize);
    TEST_ASSERT(subCount != mp.subscriberCount);
    TEST_ASSERT(initSeq != mp.sequence);
    TEST_ASSERT((mpSubscriber_t*)&subList != mp.subscribers);

    mp_init(&mp, (mpSubscriber_t*)&subList, subCount, dataSize);

    TEST_ASSERT(dataSize == mp.dataSize);
    TEST_ASSERT(subCount == mp.subscriberCount);
    TEST_ASSERT(initSeq == mp.sequence);
    TEST_ASSERT((mpSubscriber_t*)&subList == mp.subscribers);

    printf("Model point: %s\n", get_name(mp));
    mp_print(mp);

}
