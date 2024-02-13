#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "utils/rs_stdint.h"
#include "utils/rs_stdio.h"
#include "app/model_point.h"
#include "bsp/exp.h"

typedef struct MPKeyboardData{
    uint32_t keyMask;
} MPKeyboardData_t;

typedef struct MPKeyboard{
    mpBase_t base;
    MPKeyboardData_t data;
} MPKeyboard_t;

void keyboard_mp_init(MPKeyboard_t* kb, mpSubscriber_t* subscriberList, uint8_t subscriberCount);


void keyboard_init();
void get_pressed_keys();

void print_keyboard_state(MPKeyboard_t mp);

#define KEY_INDEX_Si 0
#define KEY_INDEX_Ti 1
#define KEY_INDEX_K 2
#define KEY_INDEX_Pi 3
#define KEY_INDEX_W 4
#define KEY_INDEX_H 5
#define KEY_INDEX_Ri 6
#define KEY_INDEX_A 7
#define KEY_INDEX_O 8
#define KEY_INDEX_STAR 9
#define KEY_INDEX_E 10
#define KEY_INDEX_U 11
#define KEY_INDEX_F 12
#define KEY_INDEX_Rf 13
#define KEY_INDEX_Pf 14
#define KEY_INDEX_B 15
#define KEY_INDEX_L 16
#define KEY_INDEX_G 17
#define KEY_INDEX_Tf 18
#define KEY_INDEX_Sf 19
#define KEY_INDEX_D 20
#define KEY_INDEX_Z 21
#define KEY_INDEX_NUM 22


#endif