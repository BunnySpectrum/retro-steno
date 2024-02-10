
#include "keyboard.h"

void keyboard_mp_init(MPKeyboard_t* kb, mpSubscriber_t* subscriberList, uint8_t subscriberCount){
   mp_init(&kb->base, subscriberList, subscriberCount, sizeof(MPKeyboardData_t));

   kb->data.value = 0;

}

void keyboard_init(){
    return;
}

void get_pressed_keys(){
    return;
}