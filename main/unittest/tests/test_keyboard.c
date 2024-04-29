// #include <stdio.h>
#include "utils/rs_stdio.h"

#include "unity.h"
#include "test_keyboard.h"

char checkBuffer[KEYBOARD_LINE_COUNT * KEYBOARD_LINE_LENGTH] = "";

uint32_t idToCol[] = {0, 1, 1, 2, 2, 3, 3, 2, 3, 4, 5, 6, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9};
uint32_t idToRow[] = {1, 1, 2, 1, 2, 1, 2, 3, 3, 1, 3, 3, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2};

void init_check_buffer(uint32_t keyMask){
    int count = 0;

    for (int i = 0; i < KEYBOARD_LINE_COUNT; i++)
    {
        count += snprintf(checkBuffer + count, KEYBOARD_CHAR_WIDTH + 1, " . ");
        count += snprintf(checkBuffer + count, KEYBOARD_CHAR_WIDTH + 1, " . ");
        count += snprintf(checkBuffer + count, KEYBOARD_CHAR_WIDTH + 1, " . ");
        count += snprintf(checkBuffer + count, KEYBOARD_CHAR_WIDTH + 1, " . ");
        count += snprintf(checkBuffer + count, KEYBOARD_CHAR_WIDTH + 1, " . ");
        count += snprintf(checkBuffer + count, KEYBOARD_CHAR_WIDTH + 1, " . ");
        count += snprintf(checkBuffer + count, KEYBOARD_CHAR_WIDTH + 1, " . ");
        count += snprintf(checkBuffer + count, KEYBOARD_CHAR_WIDTH + 1, " . ");
        count += snprintf(checkBuffer + count, KEYBOARD_CHAR_WIDTH + 1, " . ");
        count += snprintf(checkBuffer + count, KEYBOARD_CHAR_WIDTH + 1, " . ");
        count += snprintf(checkBuffer + count, 2, "\n");
    }
    // Separator in first line
    checkBuffer[0*31 + 4*KEYBOARD_CHAR_WIDTH + 1] = '|';

    // Blank spots in 3rd line
    checkBuffer[2*31 + 0*KEYBOARD_CHAR_WIDTH + 1] = ' ';
    checkBuffer[2*31 + 4*KEYBOARD_CHAR_WIDTH + 1] = ' ';

    // Blank spots in 4th line
    checkBuffer[3*31 + 0*KEYBOARD_CHAR_WIDTH + 1] = ' ';
    checkBuffer[3*31 + 1*KEYBOARD_CHAR_WIDTH + 1] = ' ';
    checkBuffer[3*31 + 4*KEYBOARD_CHAR_WIDTH + 1] = ' ';
    checkBuffer[3*31 + 7*KEYBOARD_CHAR_WIDTH + 1] = ' ';
    checkBuffer[3*31 + 8*KEYBOARD_CHAR_WIDTH + 1] = ' ';
    checkBuffer[3*31 + 9*KEYBOARD_CHAR_WIDTH + 1] = ' ';

    uint32_t bitTest = 0;
    uint32_t row, col;
    while(keyMask > 0){
        if( (keyMask & 0x1) != 0){
            row = idToRow[bitTest];
            col = idToCol[bitTest];
            checkBuffer[row*31 + col*KEYBOARD_CHAR_WIDTH + 1] = '*';
        }
        keyMask >>= 1;
        bitTest++;
    }
}

void dump_check_buf(){
    for(int x=0; x < KEYBOARD_LINE_COUNT * KEYBOARD_LINE_LENGTH; x++){
        printf("%c", checkBuffer[x]);
    }
    printf("\n");
}


void test_print_keyboard_state(void) {
    uint8_t dataSize = sizeof(MPKeyboardData_t);
    uint8_t subCount = 2;
    Logger_s logger;
    logger.printer = &mock_vsnprintf;



    mpSubscriber_t subList[] = {(mpSubscriber_t){.startSequence=2}, (mpSubscriber_t){.startSequence=3}}; 

    MPKeyboard_t kb;
    kb.base.name = "keyboard-init";

    keyboard_mp_init(&kb, (mpSubscriber_t*)&subList, subCount);

    /*
        4 lines, each has 31 chars (10 prints of 3 characters, followed by single newline) 
        124 chars total
    */
    // init_check_buffer(1<<9);
    // for (int i = 0; i < 0x3FFFFF; i++)
    uint32_t testKeys[] = {0x3FFFFF, 0x1, 0x3, 0x5, 0x70, 0x90, 0x100, 0x130};
    for (int i = 0; i < 8; i++)
    {
        kb.data.keyMask = testKeys[i];
        init_check_buffer(kb.data.keyMask);
        start_log_buf();
        print_keyboard_state(logger, kb);
        // dump_buffer();
        // dump_check_buf();
        TEST_ASSERT_EQUAL(0, compare_buffer(checkBuffer, KEYBOARD_LINE_COUNT * KEYBOARD_LINE_LENGTH));
    }
}