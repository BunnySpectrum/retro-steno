
#include "keyboard.h"
// #include "pico/stdio.h"
// #include "tusb.h"


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

void print_keyboard_state(Logger_s logger, MPKeyboard_t mp){

    rs_log(logger, " . ");
    rs_log(logger, " . ");
    rs_log(logger, " . ");
    rs_log(logger, " . ");
    rs_log(logger, " | ");
    rs_log(logger, " . ");
    rs_log(logger, " . ");
    rs_log(logger, " . ");
    rs_log(logger, " . ");
    rs_log(logger, " . ");
    rs_log(logger, "\n");

    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_Si)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_Ti)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_Pi)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_H)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_STAR)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_F)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_Pf)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_L)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_Tf)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_D)) > 0 ? '*' : '.');
    rs_log(logger, "\n");

    rs_log(logger, " . ");
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_K)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_W)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_Ri)) > 0 ? '*' : '.');
    rs_log(logger, "   ");
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_Rf)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_B)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_G)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_Sf)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_Z)) > 0 ? '*' : '.');
    rs_log(logger, "\n");

    rs_log(logger, "   ");
    rs_log(logger, "   ");
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_A)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_O)) > 0 ? '*' : '.');
    rs_log(logger, "   ");
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_E)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (mp.data.keyMask & (1<<KEY_INDEX_U)) > 0 ? '*' : '.');
    rs_log(logger, "   ");
    rs_log(logger, "   ");
    rs_log(logger, "   ");
    rs_log(logger, "\n");

}

void send_keyboard_state(MPKeyboard_t mp){
    uint8_t packet[6] = {0x80, 0, 0, 0, 0, 0};

    // packet[GEM_KEY_BYTE_n3] |= ((mp.data.keyMask >> KEY_INDEX_NUM) & (mp.data.keyMask >> KEY_INDEX_Ti) & 0x1)<< GEM_KEY_INDEX_n3;
    // packet[GEM_KEY_BYTE_n4] |= ((mp.data.keyMask >> KEY_INDEX_NUM) & (mp.data.keyMask >> KEY_INDEX_Pi) & 0x1)<< GEM_KEY_INDEX_n4;
    // packet[GEM_KEY_BYTE_n5] |= ((mp.data.keyMask >> KEY_INDEX_NUM) & (mp.data.keyMask >> KEY_INDEX_H) & 0x1)<< GEM_KEY_INDEX_n5;
    // packet[GEM_KEY_BYTE_n6] |= ((mp.data.keyMask >> KEY_INDEX_NUM) & (mp.data.keyMask >> KEY_INDEX_STAR) & 0x1)<< GEM_KEY_INDEX_n6;
    // packet[GEM_KEY_BYTE_n8] |= ((mp.data.keyMask >> KEY_INDEX_NUM) & (mp.data.keyMask >> KEY_INDEX_F) & 0x1)<< GEM_KEY_INDEX_n8;
    // packet[GEM_KEY_BYTE_n9] |= ((mp.data.keyMask >> KEY_INDEX_NUM) & (mp.data.keyMask >> KEY_INDEX_Pf) & 0x1)<< GEM_KEY_INDEX_n9;
    // packet[GEM_KEY_BYTE_nA] |= ((mp.data.keyMask >> KEY_INDEX_NUM) & (mp.data.keyMask >> KEY_INDEX_L) & 0x1)<< GEM_KEY_INDEX_nA;
    // packet[GEM_KEY_BYTE_nB] |= ((mp.data.keyMask >> KEY_INDEX_NUM) & (mp.data.keyMask >> KEY_INDEX_Tf) & 0x1)<< GEM_KEY_INDEX_nB;
    // packet[GEM_KEY_BYTE_nC] |= ((mp.data.keyMask >> KEY_INDEX_NUM) & (mp.data.keyMask >> KEY_INDEX_D) & 0x1)<< GEM_KEY_INDEX_nC;

    packet[GEM_KEY_BYTE_Si1] |= ((mp.data.keyMask >> KEY_INDEX_Si) & 0x1) << GEM_KEY_INDEX_Si1;
    packet[GEM_KEY_BYTE_Si2] |= ((mp.data.keyMask >> KEY_INDEX_Si) & 0x1) << GEM_KEY_INDEX_Si2;
    packet[GEM_KEY_BYTE_Ti] |= ((mp.data.keyMask >> KEY_INDEX_Ti) & 0x1) << GEM_KEY_INDEX_Ti;
    packet[GEM_KEY_BYTE_Pi] |= ((mp.data.keyMask >> KEY_INDEX_Pi) & 0x1) << GEM_KEY_INDEX_Pi;
    packet[GEM_KEY_BYTE_H] |= ((mp.data.keyMask >> KEY_INDEX_H) & 0x1) << GEM_KEY_INDEX_H;
    packet[GEM_KEY_BYTE_STAR1] |= ((mp.data.keyMask >> KEY_INDEX_STAR) & 0x1) << GEM_KEY_INDEX_STAR1;
    packet[GEM_KEY_BYTE_STAR3] |= ((mp.data.keyMask >> KEY_INDEX_STAR) & 0x1) << GEM_KEY_INDEX_STAR3;
    packet[GEM_KEY_BYTE_F] |= ((mp.data.keyMask >> KEY_INDEX_F) & 0x1) << GEM_KEY_INDEX_F;
    packet[GEM_KEY_BYTE_Pf] |= ((mp.data.keyMask >> KEY_INDEX_Pf) & 0x1) << GEM_KEY_INDEX_Pf;
    packet[GEM_KEY_BYTE_L] |= ((mp.data.keyMask >> KEY_INDEX_L) & 0x1) << GEM_KEY_INDEX_L;
    packet[GEM_KEY_BYTE_Tf] |= ((mp.data.keyMask >> KEY_INDEX_Tf) & 0x1) << GEM_KEY_INDEX_Tf;
    packet[GEM_KEY_BYTE_D] |= ((mp.data.keyMask >> KEY_INDEX_D) & 0x1) << GEM_KEY_INDEX_D;


    packet[GEM_KEY_BYTE_K] |= ((mp.data.keyMask >> KEY_INDEX_K) & 0x1) << GEM_KEY_INDEX_K;
    packet[GEM_KEY_BYTE_W] |= ((mp.data.keyMask >> KEY_INDEX_W) & 0x1) << GEM_KEY_INDEX_W;
    packet[GEM_KEY_BYTE_Ri] |= ((mp.data.keyMask >> KEY_INDEX_Ri) & 0x1) << GEM_KEY_INDEX_Ri;
    packet[GEM_KEY_BYTE_STAR2] |= ((mp.data.keyMask >> KEY_INDEX_STAR) & 0x1) << GEM_KEY_INDEX_STAR2;
    packet[GEM_KEY_BYTE_STAR4] |= ((mp.data.keyMask >> KEY_INDEX_STAR) & 0x1) << GEM_KEY_INDEX_STAR4;
    packet[GEM_KEY_BYTE_Rf] |= ((mp.data.keyMask >> KEY_INDEX_Rf) & 0x1) << GEM_KEY_INDEX_Rf;
    packet[GEM_KEY_BYTE_B] |= ((mp.data.keyMask >> KEY_INDEX_B) & 0x1) << GEM_KEY_INDEX_B;
    packet[GEM_KEY_BYTE_G] |= ((mp.data.keyMask >> KEY_INDEX_G) & 0x1) << GEM_KEY_INDEX_G;
    packet[GEM_KEY_BYTE_Sf] |= ((mp.data.keyMask >> KEY_INDEX_Sf) & 0x1) << GEM_KEY_INDEX_Sf;
    packet[GEM_KEY_BYTE_Z] |= ((mp.data.keyMask >> KEY_INDEX_Z) & 0x1) << GEM_KEY_INDEX_Z;

    packet[GEM_KEY_BYTE_A] |= ((mp.data.keyMask >> KEY_INDEX_A) & 0x1) << GEM_KEY_INDEX_A;
    packet[GEM_KEY_BYTE_O] |= ((mp.data.keyMask >> KEY_INDEX_O) & 0x1) << GEM_KEY_INDEX_O;
    packet[GEM_KEY_BYTE_E] |= ((mp.data.keyMask >> KEY_INDEX_E) & 0x1) << GEM_KEY_INDEX_E;
    packet[GEM_KEY_BYTE_U] |= ((mp.data.keyMask >> KEY_INDEX_U) & 0x1) << GEM_KEY_INDEX_U;


    for(uint8_t index=0; index < 6; index++){
        putchar(packet[index]);
    }

}