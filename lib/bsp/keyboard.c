
#include "keyboard.h"
// #include "pico/stdio.h"
// #include "tusb.h"

PinInputFSM_e keyInputState;
void (*pressCallback)(unsigned int, uint32_t);
uint8_t streamMode;
Logger_s keyboardLogger;
MPKeyboard_t *MPKeyboard;
uint8_t i2cID;

void keyboard_mp_init(MPKeyboard_t* kb, mpSubscriber_t* subscriberList, uint8_t subscriberCount){
   mp_init(&kb->base, subscriberList, subscriberCount, sizeof(MPKeyboardData_t));

   kb->data.keyMask = 0;

}

void keyboard_init(void (*callback)(unsigned int, uint32_t), Logger_s logger, MPKeyboard_t *mp, uint8_t i2cID){
    keyInputState = RS_PIN_STATE_HIGH; 
    pressCallback = callback;
    streamMode = 0;
    keyboardLogger = logger;
    MPKeyboard = mp;
    i2cID = i2cID;
    return;
}

void enable_stream_mode(){
    streamMode = 1;
}

void disable_stream_mode(){
    streamMode = 0;
}

void toggle_stream_mode(){
    streamMode ^= 0x1;
}

void cmd_get_pressed_keys(){
    uint8_t keyState[4];
    if(RS_CODE_OK == read_keys(i2cID, keyState, MPKeyboard)){
        printf(" \"read keys\", \"value\": ");
        printf("[%#x, %#x, %#x, %#x, ", keyState[0]&0xFF, keyState[1]&0x0F, keyState[2]&0x0E, keyState[3]&0xFF);
        printf("%#x]", MPKeyboard->data.keyMask);
        printf("\n");
        print_keyboard_state(keyboardLogger, *MPKeyboard);
    }
}

void handle_key_debounce(){
    RS_BOOL_e pinState = RS_FALSE;
    uint8_t keyState[4];

    switch (keyInputState){
        case RS_PIN_STATE_HIGH:
            rs_gpio_get(PIN_KEY_ENTER, &pinState);
            if(pinState == 0){ // we are now low
                keyInputState = RS_PIN_STATE_LOW;
                // printf("Pressed: %d\n", pressCounter++);
                rs_gpio_set_irq_with_callback(PIN_KEY_ENTER, RS_GPIO_IRQ_EDGE_RISE, RS_TRUE, pressCallback);
                if(RS_CODE_OK == read_keys(I2C_ID, keyState, MPKeyboard)){
                    if(streamMode != 0){
                        send_keyboard_state(*MPKeyboard);
                    }else{
                        // printf("%#x, %#x, %#x, %#x\n", keyState[0]&0xFF, keyState[1]&0x0F, keyState[2]&0x0E, keyState[3]&0xFF);
                        // printf("\t%#lx\n", mpKeyboard.data.keyMask);
                        print_keyboard_state(keyboardLogger, *MPKeyboard);
                    }
                }
            }
            //else this was a bounce
            break;

        case RS_PIN_STATE_LOW:
            rs_gpio_get(PIN_KEY_ENTER, &pinState);
            if(pinState == 1){ // we are now high
                keyInputState = RS_PIN_STATE_HIGH;
                // printf("Released: %d\n", releaseCounter++);
                rs_gpio_set_irq_with_callback(PIN_KEY_ENTER, RS_GPIO_IRQ_EDGE_FALL, RS_TRUE, pressCallback);
            }
            //else this was a bounce
            break;
        default:
            break;
        
    }
    
}


RS_CODE_e read_keys(uint8_t i2cID, uint8_t* keys, MPKeyboard_t* mp){
    uint8_t i2cData;

    i2cResponse_t scratch;
    scratch.length = 1;
    scratch.data = &i2cData;

    keys[0] = 0;
    keys[1] = 0;
    keys[2] = 0;
    keys[3] = 0;

    if (rs_i2c_read(i2cID, EXP_0, &scratch, 0) != RS_CODE_OK){
        printf("err addr %x\n", EXP_0);
        return RS_CODE_ERR;
    }else{
        keys[0] = *(scratch.data);
    }

    if (rs_i2c_read(i2cID, EXP_1, &scratch, 0) != RS_CODE_OK){
        printf("err addr %x\n", EXP_1);
        return RS_CODE_ERR;
    }else{
        keys[1] = *(scratch.data);
        // data |= (uint32_t)(*(scratch.data)) << 8;
    }

    if (rs_i2c_read(i2cID, EXP_2, &scratch, 0) != RS_CODE_OK){
        printf("err addr %x\n", EXP_2);
        return RS_CODE_ERR;
    }else{
        keys[2] = *(scratch.data);
        // data |= (uint32_t)(*(scratch.data)) << 16;
    }

    if (rs_i2c_read(i2cID, EXP_3, &scratch, 0) != RS_CODE_OK){
        printf("err addr %x\n", EXP_3);
        return RS_CODE_ERR;
    }else{
        keys[3] = *(scratch.data);
        // data |= (uint32_t)(*(scratch.data)) << 24;
    }

    mp->data.keyMask = 0;
    mp->data.keyMask |= ((keys[EXP_KEY_Si_CHIP]>>EXP_KEY_Si_INDEX) & 0x1) << KEY_INDEX_Si;
    mp->data.keyMask |= ((keys[EXP_KEY_Ti_CHIP]>>EXP_KEY_Ti_INDEX) & 0x1) << KEY_INDEX_Ti;
    mp->data.keyMask |= ((keys[EXP_KEY_K_CHIP]>>EXP_KEY_K_INDEX) & 0x1) << KEY_INDEX_K;
    mp->data.keyMask |= ((keys[EXP_KEY_Pi_CHIP]>>EXP_KEY_Pi_INDEX) & 0x1) << KEY_INDEX_Pi;
    mp->data.keyMask |= ((keys[EXP_KEY_W_CHIP]>>EXP_KEY_W_INDEX) & 0x1) << KEY_INDEX_W;
    mp->data.keyMask |= ((keys[EXP_KEY_H_CHIP]>>EXP_KEY_H_INDEX) & 0x1) << KEY_INDEX_H;
    mp->data.keyMask |= ((keys[EXP_KEY_Ri_CHIP]>>EXP_KEY_Ri_INDEX) & 0x1) << KEY_INDEX_Ri;
    mp->data.keyMask |= ((keys[EXP_KEY_A_CHIP]>>EXP_KEY_A_INDEX) & 0x1) << KEY_INDEX_A;
    mp->data.keyMask |= ((keys[EXP_KEY_O_CHIP]>>EXP_KEY_O_INDEX) & 0x1) << KEY_INDEX_O;
    mp->data.keyMask |= ((keys[EXP_KEY_STAR_CHIP]>>EXP_KEY_STAR_INDEX) & 0x1) << KEY_INDEX_STAR;
    mp->data.keyMask |= ((keys[EXP_KEY_E_CHIP]>>EXP_KEY_E_INDEX) & 0x1) << KEY_INDEX_E;
    mp->data.keyMask |= ((keys[EXP_KEY_U_CHIP]>>EXP_KEY_U_INDEX) & 0x1) << KEY_INDEX_U;
    mp->data.keyMask |= ((keys[EXP_KEY_F_CHIP]>>EXP_KEY_F_INDEX) & 0x1) << KEY_INDEX_F;
    mp->data.keyMask |= ((keys[EXP_KEY_Rf_CHIP]>>EXP_KEY_Rf_INDEX) & 0x1) << KEY_INDEX_Rf;
    mp->data.keyMask |= ((keys[EXP_KEY_Pf_CHIP]>>EXP_KEY_Pf_INDEX) & 0x1) << KEY_INDEX_Pf;
    mp->data.keyMask |= ((keys[EXP_KEY_B_CHIP]>>EXP_KEY_B_INDEX) & 0x1) << KEY_INDEX_B;
    mp->data.keyMask |= ((keys[EXP_KEY_L_CHIP]>>EXP_KEY_L_INDEX) & 0x1) << KEY_INDEX_L;
    mp->data.keyMask |= ((keys[EXP_KEY_G_CHIP]>>EXP_KEY_G_INDEX) & 0x1) << KEY_INDEX_G;
    mp->data.keyMask |= ((keys[EXP_KEY_Tf_CHIP]>>EXP_KEY_Tf_INDEX) & 0x1) << KEY_INDEX_Tf;
    mp->data.keyMask |= ((keys[EXP_KEY_Sf_CHIP]>>EXP_KEY_Sf_INDEX) & 0x1) << KEY_INDEX_Sf;
    mp->data.keyMask |= ((keys[EXP_KEY_D_CHIP]>>EXP_KEY_D_INDEX) & 0x1) << KEY_INDEX_D;
    mp->data.keyMask |= ((keys[EXP_KEY_Z_CHIP]>>EXP_KEY_Z_INDEX) & 0x1) << KEY_INDEX_Z;
    mp->data.keyMask |= ((keys[EXP_KEY_NUM_CHIP]>>EXP_KEY_NUM_INDEX) & 0x1) << KEY_INDEX_NUM;

    return RS_CODE_OK;
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

    rs_log(logger, "   ");
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