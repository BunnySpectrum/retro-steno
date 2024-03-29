#include "model_point.h"

#include "utils/rs_string.h"
#include "utils/rs_stdio.h"

void mp_init(mpBase_t* mp, mpSubscriber_t* subscriberList, uint8_t subscriberCount, size_t dataSize){
    mp->subscribers = subscriberList;
    //rs_strcpy(mp.name, name) // for now let name be set externally
    mp->dataSize = dataSize;
    mp->sequence = 1;
    mp->valid = MP_INVALID;
    mp->locked = mpLockReqUnlock;
    mp->subscriberCount = subscriberCount;

}

const char* mp_get_name(mpBase_t mp){
    return mp.name;
}

uint16_t mp_get_sequence(mpBase_t mp){
    return mp.sequence;
}


uint8_t mp_is_valid(mpBase_t mp, uint16_t* seqNumPtr){
    *seqNumPtr = mp.sequence;
    return mp.valid == MP_VALID;
}

uint8_t mp_is_locked(mpBase_t mp){
    return mp.locked == mpLockReqLock;
}


uint16_t mp_set_lock_state(mpBase_t* mp, ModelPointLockReq_e lockRequest){
    if(lockRequest != mpLockReqNone){
        mp->locked = lockRequest;
    }
    return mp->sequence;
}

uint16_t mp_set_invalid(mpBase_t* mp, ModelPointLockReq_e lockRequest){
    mp_set_lock_state(mp, lockRequest);
    mp->valid = MP_INVALID;

    return mp->sequence;
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