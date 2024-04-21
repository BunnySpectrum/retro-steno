// #include <stdio.h>
#include "utils/rs_stdio.h"

#include "unity.h"
#include "test_keyboard.h"




void test_print_keyboard_state(void) {
    uint8_t dataSize = sizeof(MPKeyboardData_t);
    uint8_t subCount = 2;
    Logger_s logger;
    logger.printer = &mock_vsnprintf;



    mpSubscriber_t subList[] = {(mpSubscriber_t){.startSequence=2}, (mpSubscriber_t){.startSequence=3}}; 

    MPKeyboard_t kb;
    kb.base.name = "keyboard-init";

    keyboard_mp_init(&kb, (mpSubscriber_t*)&subList, subCount);
    kb.data.keyMask = 0x33;

    /*
        4 lines, each has 31 chars (10 prints of 3 characters, followed by single newline) 
        128 chars total
    */
    start_log_buf();
    print_keyboard_state(logger, kb);
    dump_buffer();
}