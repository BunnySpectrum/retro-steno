#ifndef _MODEL_POINT_H_
#define _MODEL_POINT_H_
// From Patterns in the Machine
//  * value stored should be data, not another object. A struct of values is alright
//  * all read and write operations are specific to the model point's value type
//  * accessing values is thread safe
//  * have valid or invalid state independent of their value
//  * have a subscription mechanism for clients to receive change notificvations when value or valid state changes

#include <stdint.h>
#include <stddef.h>

// The following is derived from the ModelPoint design from the PIM book.
// I've made some modifications below to avoid adding linked lists or dynamic allocation
// c.f. pim\src\Cpl\Dm\ModelPoint.h
// c.f. pim\src\Cpl\Dm\ModelPointCommon_.h



#define MP_VALID 1
#define MP_INVALID 0

// I mostly forsee this being used for testing
typedef enum ModelPointLockReq{
    mpLockReqNone,
    mpLockReqLock, // when locked, mp state becomes read-only. 
    mpLockReqUnlock,
} ModelPointLockReq_e;


//forward declarations
typedef struct mpBase mpBase_t; 
typedef struct mpSubscriber mpSubscriber_t;


typedef struct mpSubscriber{
    void (*changeCallback)(mpBase_t modelPoint, mpSubscriber_t subscriber);
    mpBase_t* modelPoint;
    uint16_t startSequence;
} mpSubscriber_t;

// Global list of subscribers
static mpSubscriber_t *activeSubscribers;
static uint8_t subscriberCount = 0;


// To keep things simpler at first, I'm planning to use a single base model point struct
// This prevents me from using the compiler to detect using the wrong struct in the wrong place...but for now that's alright
// If I later want distinct types of model points, I could use the idiom:
/*
typedef struct mp<some name>{
    mpBase_t mpBase;
    // new fields go here
} mp<some name>_t
*/
typedef struct mpBase{
    mpSubscriber_t *subscribers; //for now, choosing to create all subscribers at compile time
    const char* name;   // assumed unique, but not enforced 
    void* data;
    size_t dataSize;
    uint16_t sequence; // wraps around, but will never be zero
    uint8_t valid;
    uint8_t locked;
    uint8_t subscriberCount;
} mpBase_t;

// Global list of model points
//  Note that this alone won't work if derived model point structs are created
static mpBase_t *activeModelPoints;
static uint8_t activeModelPointCount = 0;


// Constructor
void mp_init(mpBase_t* mp, mpSubscriber_t* subscriberList, uint8_t subscriberCount, size_t dataSize);

// Public interface
const char* get_name(mpBase_t);
//size_t get_size(mpBase_t); // not including since mpBase is always same size
uint16_t get_sequence(mpBase_t);
void touch(mpBase_t); // triggers change notifications, but doesn't change any mp state
uint16_t set_invalid(mpBase_t, ModelPointLockReq_e lockRequest); //returns sequence value
uint8_t is_not_valid(mpBase_t, uint16_t* seqNumPtr); // returns true if valid; also sets current sequence number
uint8_t is_locked(mpBase_t); //returns if locked or not
uint16_t set_lock_state(mpBase_t, ModelPointLockReq_e lockRequest);
void mp_print(mpBase_t);


// Private interface
// Increment sequence, and notify any subscribers
// Not triggered by lock state change
static void process_change_notifications(mpBase_t mp);


#endif
