#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "utils/rs_stdint.h"
#include "app/model_point.h"
#include "bsp/exp.h"

typedef struct MPKeyboardData{
    uint8_t value;
} MPKeyboardData_t;

typedef struct MPKeyboard{
    mpBase_t base;
    MPKeyboardData_t data;
} MPKeyboard_t;

void keyboard_mp_init(MPKeyboard_t* kb, mpSubscriber_t* subscriberList, uint8_t subscriberCount);


void keyboard_init();
void get_pressed_keys();



#endif