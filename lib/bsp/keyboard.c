
#include "keyboard.h"
// #include "pico/stdio.h"
// #include "tusb.h"

PinInputFSM_e keyInputState;
void (*pressCallback)(unsigned int, uint32_t);
uint8_t streamMode;
Logger_s keyboardLogger;
static MPKeyboard_t *pMPKeyboard;
uint8_t i2cID;

void keyboard_mp_init(MPKeyboard_t* kb, mpSubscriber_t* subscriberList, uint8_t subscriberCount){
   mp_init(&kb->base, subscriberList, subscriberCount, sizeof(MPKeyboardData_t));
   kb->base.pData = & kb->data;

   kb->data.keyMask = 0;

}

RS_CODE_e mp_keyboard_get_data(MPKeyboard_t* mp, MPKeyboardData_t* pData){
    mp_get_data((mpBase_t*)mp, pData, sizeof(MPKeyboardData_t), critical_section);
}


RS_CODE_e mp_keyboard_set_data(MPKeyboard_t* mp, MPKeyboardData_t* pData){
    mp_set_data((mpBase_t*)mp, pData, sizeof(MPKeyboardData_t), critical_section);
}

void keyboard_init(void (*callback)(unsigned int, uint32_t), Logger_s logger, MPKeyboard_t *mp, uint8_t i2cID){
    keyInputState = RS_PIN_STATE_HIGH; 
    pressCallback = callback;
    streamMode = 0;
    keyboardLogger = logger;
    pMPKeyboard = mp;
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
    MPKeyboardData_t data;
    if(RS_CODE_OK == read_keys(i2cID, keyState, &data)){
        printf(" \"read keys\", \"value\": ");
        printf("[%#x, %#x, %#x, %#x, ", keyState[0]&0xFF, keyState[1]&0x0F, keyState[2]&0x0E, keyState[3]&0xFF);
        printf("%#x]", data.keyMask);
        printf("\n");
        print_keyboard_state(keyboardLogger, &data);
    }
}

void handle_key_debounce(){
    RS_BOOL_e pinState = RS_FALSE;
    uint8_t keyState[4];
    MPKeyboardData_t data;

    switch (keyInputState){
        case RS_PIN_STATE_HIGH:
            rs_gpio_get(PIN_KEY_ENTER, &pinState);
            if(pinState == 0){ // we are now low
                keyInputState = RS_PIN_STATE_LOW;
                
                rs_gpio_set_irq_with_callback(PIN_KEY_ENTER, RS_GPIO_IRQ_EDGE_RISE, RS_TRUE, pressCallback);
                if(RS_CODE_OK == read_keys(I2C_ID, keyState, &data)){
                    // Have new chord
                    mp_keyboard_set_data(pMPKeyboard, &data);

                    if(streamMode != 0){
                        send_keyboard_state(&data);
                    }else{
                        print_keyboard_state(keyboardLogger, &data);
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


RS_CODE_e read_keys(uint8_t i2cID, uint8_t* keys, MPKeyboardData_t *pData){
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

    pData->keyMask = 0;
    pData->keyMask |= ((keys[EXP_KEY_Si_CHIP]>>EXP_KEY_Si_INDEX) & 0x1) << KEY_INDEX_Si;
    pData->keyMask |= ((keys[EXP_KEY_Ti_CHIP]>>EXP_KEY_Ti_INDEX) & 0x1) << KEY_INDEX_Ti;
    pData->keyMask |= ((keys[EXP_KEY_K_CHIP]>>EXP_KEY_K_INDEX) & 0x1) << KEY_INDEX_K;
    pData->keyMask |= ((keys[EXP_KEY_Pi_CHIP]>>EXP_KEY_Pi_INDEX) & 0x1) << KEY_INDEX_Pi;
    pData->keyMask |= ((keys[EXP_KEY_W_CHIP]>>EXP_KEY_W_INDEX) & 0x1) << KEY_INDEX_W;
    pData->keyMask |= ((keys[EXP_KEY_H_CHIP]>>EXP_KEY_H_INDEX) & 0x1) << KEY_INDEX_H;
    pData->keyMask |= ((keys[EXP_KEY_Ri_CHIP]>>EXP_KEY_Ri_INDEX) & 0x1) << KEY_INDEX_Ri;
    pData->keyMask |= ((keys[EXP_KEY_A_CHIP]>>EXP_KEY_A_INDEX) & 0x1) << KEY_INDEX_A;
    pData->keyMask |= ((keys[EXP_KEY_O_CHIP]>>EXP_KEY_O_INDEX) & 0x1) << KEY_INDEX_O;
    pData->keyMask |= ((keys[EXP_KEY_STAR_CHIP]>>EXP_KEY_STAR_INDEX) & 0x1) << KEY_INDEX_STAR;
    pData->keyMask |= ((keys[EXP_KEY_E_CHIP]>>EXP_KEY_E_INDEX) & 0x1) << KEY_INDEX_E;
    pData->keyMask |= ((keys[EXP_KEY_U_CHIP]>>EXP_KEY_U_INDEX) & 0x1) << KEY_INDEX_U;
    pData->keyMask |= ((keys[EXP_KEY_F_CHIP]>>EXP_KEY_F_INDEX) & 0x1) << KEY_INDEX_F;
    pData->keyMask |= ((keys[EXP_KEY_Rf_CHIP]>>EXP_KEY_Rf_INDEX) & 0x1) << KEY_INDEX_Rf;
    pData->keyMask |= ((keys[EXP_KEY_Pf_CHIP]>>EXP_KEY_Pf_INDEX) & 0x1) << KEY_INDEX_Pf;
    pData->keyMask |= ((keys[EXP_KEY_B_CHIP]>>EXP_KEY_B_INDEX) & 0x1) << KEY_INDEX_B;
    pData->keyMask |= ((keys[EXP_KEY_L_CHIP]>>EXP_KEY_L_INDEX) & 0x1) << KEY_INDEX_L;
    pData->keyMask |= ((keys[EXP_KEY_G_CHIP]>>EXP_KEY_G_INDEX) & 0x1) << KEY_INDEX_G;
    pData->keyMask |= ((keys[EXP_KEY_Tf_CHIP]>>EXP_KEY_Tf_INDEX) & 0x1) << KEY_INDEX_Tf;
    pData->keyMask |= ((keys[EXP_KEY_Sf_CHIP]>>EXP_KEY_Sf_INDEX) & 0x1) << KEY_INDEX_Sf;
    pData->keyMask |= ((keys[EXP_KEY_D_CHIP]>>EXP_KEY_D_INDEX) & 0x1) << KEY_INDEX_D;
    pData->keyMask |= ((keys[EXP_KEY_Z_CHIP]>>EXP_KEY_Z_INDEX) & 0x1) << KEY_INDEX_Z;
    pData->keyMask |= ((keys[EXP_KEY_NUM_CHIP]>>EXP_KEY_NUM_INDEX) & 0x1) << KEY_INDEX_NUM;

    return RS_CODE_OK;
}












void print_keyboard_state(Logger_s logger, MPKeyboardData_t *pData){

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

    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_Si)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_Ti)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_Pi)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_H)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_STAR)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_F)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_Pf)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_L)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_Tf)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_D)) > 0 ? '*' : '.');
    rs_log(logger, "\n");

    rs_log(logger, "   ");
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_K)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_W)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_Ri)) > 0 ? '*' : '.');
    rs_log(logger, "   ");
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_Rf)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_B)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_G)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_Sf)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_Z)) > 0 ? '*' : '.');
    rs_log(logger, "\n");

    rs_log(logger, "   ");
    rs_log(logger, "   ");
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_A)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_O)) > 0 ? '*' : '.');
    rs_log(logger, "   ");
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_E)) > 0 ? '*' : '.');
    rs_log(logger, " %c ", (pData->keyMask & (1<<KEY_INDEX_U)) > 0 ? '*' : '.');
    rs_log(logger, "   ");
    rs_log(logger, "   ");
    rs_log(logger, "   ");
    rs_log(logger, "\n");

}

RS_CODE_e keyboard_state_to_str(MPKeyboardData_t *pData, RS_BOOL_e *numBar, char *initial, char *vowel, char *final){
    uint8_t strIdx;

    *numBar = RS_FALSE;

    strIdx = 0;
    initial[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_Si)) > 0 ? 'S' : ' ';
    initial[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_Ti)) > 0 ? 'T' : ' ';
    initial[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_K)) > 0 ? 'K' : ' ';
    initial[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_Pi)) > 0 ? 'P' : ' ';
    initial[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_W)) > 0 ? 'W' : ' ';
    initial[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_H)) > 0 ? 'H' : ' ';
    initial[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_Ri)) > 0 ? 'R' : ' ';
    initial[strIdx] = '\0';

    strIdx = 0;
    vowel[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_A)) > 0 ? 'A' : ' ';
    vowel[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_O)) > 0 ? 'O' : ' ';
    vowel[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_STAR)) > 0 ? '*' : ' ';
    vowel[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_E)) > 0 ? 'E' : ' ';
    vowel[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_U)) > 0 ? 'U' : ' ';
    vowel[strIdx] = '\0';

    strIdx = 0;
    final[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_F)) > 0 ? 'F' : ' ';
    final[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_Rf)) > 0 ? 'R' : ' ';
    final[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_Pf)) > 0 ? 'P' : ' ';
    final[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_B)) > 0 ? 'B' : ' ';
    final[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_L)) > 0 ? 'L' : ' ';
    final[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_G)) > 0 ? 'G' : ' ';
    final[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_Tf)) > 0 ? 'T' : ' ';
    final[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_Sf)) > 0 ? 'S' : ' ';
    final[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_D)) > 0 ? 'D' : ' ';
    final[strIdx++] = (pData->keyMask & (1<<KEY_INDEX_Z)) > 0 ? 'Z' : ' ';
    final[strIdx] = '\0';

    return RS_CODE_OK;

}
void send_keyboard_state(MPKeyboardData_t *pData){
    uint8_t packet[6] = {0x80, 0, 0, 0, 0, 0};

    // packet[GEM_KEY_BYTE_n3] |= ((pData->keyMask >> KEY_INDEX_NUM) & (pData->keyMask >> KEY_INDEX_Ti) & 0x1)<< GEM_KEY_INDEX_n3;
    // packet[GEM_KEY_BYTE_n4] |= ((pData->keyMask >> KEY_INDEX_NUM) & (pData->keyMask >> KEY_INDEX_Pi) & 0x1)<< GEM_KEY_INDEX_n4;
    // packet[GEM_KEY_BYTE_n5] |= ((pData->keyMask >> KEY_INDEX_NUM) & (pData->keyMask >> KEY_INDEX_H) & 0x1)<< GEM_KEY_INDEX_n5;
    // packet[GEM_KEY_BYTE_n6] |= ((pData->keyMask >> KEY_INDEX_NUM) & (pData->keyMask >> KEY_INDEX_STAR) & 0x1)<< GEM_KEY_INDEX_n6;
    // packet[GEM_KEY_BYTE_n8] |= ((pData->keyMask >> KEY_INDEX_NUM) & (pData->keyMask >> KEY_INDEX_F) & 0x1)<< GEM_KEY_INDEX_n8;
    // packet[GEM_KEY_BYTE_n9] |= ((pData->keyMask >> KEY_INDEX_NUM) & (pData->keyMask >> KEY_INDEX_Pf) & 0x1)<< GEM_KEY_INDEX_n9;
    // packet[GEM_KEY_BYTE_nA] |= ((pData->keyMask >> KEY_INDEX_NUM) & (pData->keyMask >> KEY_INDEX_L) & 0x1)<< GEM_KEY_INDEX_nA;
    // packet[GEM_KEY_BYTE_nB] |= ((pData->keyMask >> KEY_INDEX_NUM) & (pData->keyMask >> KEY_INDEX_Tf) & 0x1)<< GEM_KEY_INDEX_nB;
    // packet[GEM_KEY_BYTE_nC] |= ((pData->keyMask >> KEY_INDEX_NUM) & (pData->keyMask >> KEY_INDEX_D) & 0x1)<< GEM_KEY_INDEX_nC;

    packet[GEM_KEY_BYTE_Si1] |= ((pData->keyMask >> KEY_INDEX_Si) & 0x1) << GEM_KEY_INDEX_Si1;
    packet[GEM_KEY_BYTE_Si2] |= ((pData->keyMask >> KEY_INDEX_Si) & 0x1) << GEM_KEY_INDEX_Si2;
    packet[GEM_KEY_BYTE_Ti] |= ((pData->keyMask >> KEY_INDEX_Ti) & 0x1) << GEM_KEY_INDEX_Ti;
    packet[GEM_KEY_BYTE_Pi] |= ((pData->keyMask >> KEY_INDEX_Pi) & 0x1) << GEM_KEY_INDEX_Pi;
    packet[GEM_KEY_BYTE_H] |= ((pData->keyMask >> KEY_INDEX_H) & 0x1) << GEM_KEY_INDEX_H;
    packet[GEM_KEY_BYTE_STAR1] |= ((pData->keyMask >> KEY_INDEX_STAR) & 0x1) << GEM_KEY_INDEX_STAR1;
    packet[GEM_KEY_BYTE_STAR3] |= ((pData->keyMask >> KEY_INDEX_STAR) & 0x1) << GEM_KEY_INDEX_STAR3;
    packet[GEM_KEY_BYTE_F] |= ((pData->keyMask >> KEY_INDEX_F) & 0x1) << GEM_KEY_INDEX_F;
    packet[GEM_KEY_BYTE_Pf] |= ((pData->keyMask >> KEY_INDEX_Pf) & 0x1) << GEM_KEY_INDEX_Pf;
    packet[GEM_KEY_BYTE_L] |= ((pData->keyMask >> KEY_INDEX_L) & 0x1) << GEM_KEY_INDEX_L;
    packet[GEM_KEY_BYTE_Tf] |= ((pData->keyMask >> KEY_INDEX_Tf) & 0x1) << GEM_KEY_INDEX_Tf;
    packet[GEM_KEY_BYTE_D] |= ((pData->keyMask >> KEY_INDEX_D) & 0x1) << GEM_KEY_INDEX_D;


    packet[GEM_KEY_BYTE_K] |= ((pData->keyMask >> KEY_INDEX_K) & 0x1) << GEM_KEY_INDEX_K;
    packet[GEM_KEY_BYTE_W] |= ((pData->keyMask >> KEY_INDEX_W) & 0x1) << GEM_KEY_INDEX_W;
    packet[GEM_KEY_BYTE_Ri] |= ((pData->keyMask >> KEY_INDEX_Ri) & 0x1) << GEM_KEY_INDEX_Ri;
    packet[GEM_KEY_BYTE_STAR2] |= ((pData->keyMask >> KEY_INDEX_STAR) & 0x1) << GEM_KEY_INDEX_STAR2;
    packet[GEM_KEY_BYTE_STAR4] |= ((pData->keyMask >> KEY_INDEX_STAR) & 0x1) << GEM_KEY_INDEX_STAR4;
    packet[GEM_KEY_BYTE_Rf] |= ((pData->keyMask >> KEY_INDEX_Rf) & 0x1) << GEM_KEY_INDEX_Rf;
    packet[GEM_KEY_BYTE_B] |= ((pData->keyMask >> KEY_INDEX_B) & 0x1) << GEM_KEY_INDEX_B;
    packet[GEM_KEY_BYTE_G] |= ((pData->keyMask >> KEY_INDEX_G) & 0x1) << GEM_KEY_INDEX_G;
    packet[GEM_KEY_BYTE_Sf] |= ((pData->keyMask >> KEY_INDEX_Sf) & 0x1) << GEM_KEY_INDEX_Sf;
    packet[GEM_KEY_BYTE_Z] |= ((pData->keyMask >> KEY_INDEX_Z) & 0x1) << GEM_KEY_INDEX_Z;

    packet[GEM_KEY_BYTE_A] |= ((pData->keyMask >> KEY_INDEX_A) & 0x1) << GEM_KEY_INDEX_A;
    packet[GEM_KEY_BYTE_O] |= ((pData->keyMask >> KEY_INDEX_O) & 0x1) << GEM_KEY_INDEX_O;
    packet[GEM_KEY_BYTE_E] |= ((pData->keyMask >> KEY_INDEX_E) & 0x1) << GEM_KEY_INDEX_E;
    packet[GEM_KEY_BYTE_U] |= ((pData->keyMask >> KEY_INDEX_U) & 0x1) << GEM_KEY_INDEX_U;


    for(uint8_t index=0; index < 6; index++){
        putchar(packet[index]);
    }

}