
#include "keyboard.h"

void keyboard_mp_init(MPKeyboard_t* kb, mpSubscriber_t* subscriberList, uint8_t subscriberCount){
   mp_init(&kb->base, subscriberList, subscriberCount, sizeof(MPKeyboardData_t));

   kb->data.keyMask = 0;

}

void keyboard_init(){
    return;
}

void get_pressed_keys(){
    return;
}

void print_keyboard_state(MPKeyboard_t mp){
    printf(" . ");
    printf(" . ");
    printf(" . ");
    printf(" . ");
    printf(" * ");
    printf(" . ");
    printf(" . ");
    printf(" . ");
    printf(" . ");
    printf(" . ");
    printf("\n");

    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_Si)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_Ti)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_Pi)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_H)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_STAR)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_F)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_Pf)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_L)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_Tf)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_D)) > 0 ? '*' : '.');
    printf("\n");

    printf(" . ");
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_K)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_W)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_Ri)) > 0 ? '*' : '.');
    printf(" . ");
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_Rf)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_B)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_G)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_Sf)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_Z)) > 0 ? '*' : '.');
    printf("\n");

    printf("   ");
    printf("   ");
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_A)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_O)) > 0 ? '*' : '.');
    printf("   ");
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_E)) > 0 ? '*' : '.');
    printf(" %c ", (mp.data.keyMask & (1<<KEY_INDEX_U)) > 0 ? '*' : '.');
    printf("   ");
    printf("   ");
    printf("   ");
    printf("\n");

}