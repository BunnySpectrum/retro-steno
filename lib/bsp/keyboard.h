#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "utils/rs_stdint.h"
#include "utils/rs_stdio.h"
#include "utils/rs_codes.h"
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
RS_CODE_e read_keys(uint8_t i2cID, uint8_t* keys, MPKeyboard_t* mp);

void print_keyboard_state(Logger_s logger, MPKeyboard_t mp);
void send_keyboard_state(MPKeyboard_t mp);

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


// Gemini first byte
#define GEM_KEY_BYTE_FN 0
#define GEM_KEY_INDEX_FN 6

#define GEM_KEY_BYTE_n1 0
#define GEM_KEY_INDEX_n1 5

#define GEM_KEY_BYTE_n2 0
#define GEM_KEY_INDEX_n2 4

#define GEM_KEY_BYTE_n3 0
#define GEM_KEY_INDEX_n3 3

#define GEM_KEY_BYTE_n4 0
#define GEM_KEY_INDEX_n4 2

#define GEM_KEY_BYTE_n5 0
#define GEM_KEY_INDEX_n5 1

#define GEM_KEY_BYTE_n6 0
#define GEM_KEY_INDEX_n6 0

// Gemini second byte
#define GEM_KEY_BYTE_Si1 1
#define GEM_KEY_INDEX_Si1 6

#define GEM_KEY_BYTE_Si2 1
#define GEM_KEY_INDEX_Si2 5

#define GEM_KEY_BYTE_Ti 1
#define GEM_KEY_INDEX_Ti 4

#define GEM_KEY_BYTE_K 1
#define GEM_KEY_INDEX_K 3

#define GEM_KEY_BYTE_Pi 1
#define GEM_KEY_INDEX_Pi 2

#define GEM_KEY_BYTE_W 1
#define GEM_KEY_INDEX_W 1

#define GEM_KEY_BYTE_H 1
#define GEM_KEY_INDEX_H 0


// Gemini third byte
#define GEM_KEY_BYTE_Ri 2
#define GEM_KEY_INDEX_Ri 6

#define GEM_KEY_BYTE_A 2
#define GEM_KEY_INDEX_A 5

#define GEM_KEY_BYTE_O 2
#define GEM_KEY_INDEX_O 4

#define GEM_KEY_BYTE_STAR1 2
#define GEM_KEY_INDEX_STAR1 3

#define GEM_KEY_BYTE_STAR2 2
#define GEM_KEY_INDEX_STAR2 2

#define GEM_KEY_BYTE_RES1 2
#define GEM_KEY_INDEX_RES1 1

#define GEM_KEY_BYTE_RES2 2
#define GEM_KEY_INDEX_RES2 0


// Gemini fourth byte
#define GEM_KEY_BYTE_PWR 3
#define GEM_KEY_INDEX_PWR 6

#define GEM_KEY_BYTE_STAR3 3
#define GEM_KEY_INDEX_STAR3 5

#define GEM_KEY_BYTE_STAR4 3
#define GEM_KEY_INDEX_STAR4 4

#define GEM_KEY_BYTE_E 3
#define GEM_KEY_INDEX_E 3

#define GEM_KEY_BYTE_U 3
#define GEM_KEY_INDEX_U 2

#define GEM_KEY_BYTE_F 3
#define GEM_KEY_INDEX_F 1

#define GEM_KEY_BYTE_Rf 3
#define GEM_KEY_INDEX_Rf 0


// Gemini fifth byte
#define GEM_KEY_BYTE_Pf 4
#define GEM_KEY_INDEX_Pf 6

#define GEM_KEY_BYTE_B 4
#define GEM_KEY_INDEX_B 5

#define GEM_KEY_BYTE_L 4
#define GEM_KEY_INDEX_L 4

#define GEM_KEY_BYTE_G 4
#define GEM_KEY_INDEX_G 3

#define GEM_KEY_BYTE_Tf 4
#define GEM_KEY_INDEX_Tf 2

#define GEM_KEY_BYTE_Sf 4
#define GEM_KEY_INDEX_Sf 1

#define GEM_KEY_BYTE_D 4
#define GEM_KEY_INDEX_D 0


// Gemini sixth byte
#define GEM_KEY_BYTE_n7 5
#define GEM_KEY_INDEX_n7 6

#define GEM_KEY_BYTE_n8 5
#define GEM_KEY_INDEX_n8 5

#define GEM_KEY_BYTE_n9 5
#define GEM_KEY_INDEX_n9 4

#define GEM_KEY_BYTE_nA 5
#define GEM_KEY_INDEX_nA 3

#define GEM_KEY_BYTE_nB 5
#define GEM_KEY_INDEX_nB 2

#define GEM_KEY_BYTE_nC 5
#define GEM_KEY_INDEX_nC 1

#define GEM_KEY_BYTE_Z 5
#define GEM_KEY_INDEX_Z 0








#endif