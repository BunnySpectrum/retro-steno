#include "model_point.h"

#include "utils/rs_string.h"

void mp_init(mpBase_t* mp, mpSubscriber_t* subscriberList, uint8_t subscriberCount, size_t dataSize){
    mp->subscribers = subscriberList;
    //rs_strcpy(mp.name, name) // for now let name be set externally
    mp->dataSize = dataSize;
    mp->sequence = 1;
    mp->valid = MP_INVALID;
    mp->locked = mpLockReqUnlock;
    mp->subscriberCount = subscriberCount;

}

const char* get_name(mpBase_t mp){
    return mp.name;
}

void mp_print(mpBase_t mp){
    printf("Name: %s\n", mp.name);
    printf("Datasize: %d\n", mp.dataSize);
    printf("Seq: %d\n", mp.sequence);
    printf("Valid: %d\n", mp.valid);
    printf("Locked: %d\n", mp.locked);
    printf("Sub Count: %d\n", mp.subscriberCount);
    printf("Sub list: %lu\n", mp.subscribers);

}