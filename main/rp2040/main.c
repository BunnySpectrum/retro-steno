//#include <stdint.h>
#include <stdio.h>


#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "pico/binary_info.h"

#include "bsp/exp.h"
#include "bsp/bsp.h"
#include "bsp/led.h"
#include "bsp/scheduler.h"
// #include "bsp/pinmap.h"
#include "hw/drv_i2c.h"
#include "hw/drv_gpio.h"
#include "bsp/keyboard.h"
#include "utils/rs_time.h"
#include "app/hbt.h"
#include "app/cli.h"


#define BLINK_LONG 500
#define BLINK_HBT 10
#define BLINK_FAST 100


#define TASK_KEY_DEBOUNCE_PERIOD_MS 25

RS_TASK_INFO_s taskHeartbeat = {.task_func = hbt_toggle, .counter = -1, .period = HBT_TASK_PERIOD_MS, .repeat = RS_TRUE};
RS_TASK_INFO_s taskCLI = {.task_func = cli_process, .counter = -1, .period = CLI_TASK_PERIOD_MS, .repeat = RS_TRUE};


volatile int16_t taskKeyDebounce = -1;

volatile uint64_t lastTimestamp = 0;


// Call this every 1 ms
bool task_period_update_1ms(struct repeating_timer *t){
    if(taskHeartbeat.counter > 0){taskHeartbeat.counter--;}
    if(taskCLI.counter > 0){taskCLI.counter--;}

    if(taskKeyDebounce > 0){taskKeyDebounce--;}

    return true;
}


// volatile bool newChar = 0;
uint64_t cbTime = 0;

void char_callback(void* data){
    newChar = 1;
    *(uint64_t*)data = time_us_64();
}

void gpio_callback(uint gpio, uint32_t events){
    taskKeyDebounce = TASK_KEY_DEBOUNCE_PERIOD_MS;
    // printf("GPIO %d %#x\n", gpio, events);
}


typedef enum PinInputFSM{
    RS_PIN_STATE_HIGH = 0,
    RS_PIN_STATE_FALL = 1,
    RS_PIN_STATE_LOW = 2,
    RS_PIN_STATE_RISE = 3
} PinInputFSM_e;


int main() {

    uint8_t flag = 0;
    uint8_t value = 0;
    i2cResponse_t i2cResp;
    uint8_t scratch8;
    i2cResp.data = &scratch8;
    i2cResp.length = 1;
    uint8_t cbParam = 0;
    int inputChar;
    uint8_t pressCounter = 0;
    uint8_t releaseCounter = 0;
    PinInputFSM_e keyInputState = RS_PIN_STATE_HIGH; 
    uint8_t keyState[4];
    MPKeyboard_t mpKeyboard;
    uint8_t streamMode = 0;
    Logger_s debugPrinter;

    debugPrinter.printer = &rs_vprintf;


    bsp_gpio_init(gpio_callback);
    bsp_usb_init(&char_callback, &cbTime);
    bsp_i2c_init(I2C_ID);

    // Make the I2C pins available to picotool
    // TBD how/if to move this out of main
    bi_decl(bi_2pins_with_func(SDA_PIN, SCL_PIN, RS_GPIO_FUNC_I2C));


    // Set up periodic tasks
    hbt_init();
    schedule_task(&taskHeartbeat);

    cli_init();
    schedule_task(&taskCLI);

    // Set up timer
    struct repeating_timer timer;
    add_repeating_timer_ms(1, &task_period_update_1ms, NULL, &timer);

    printf("Starting.\n");
    while (true) {

        if(taskKeyDebounce == 0){
            taskKeyDebounce = -1;
            switch (keyInputState){
                case RS_PIN_STATE_HIGH:
                    if(gpio_get(PIN_KEY_ENTER) == 0){ // we are now low
                        keyInputState = RS_PIN_STATE_LOW;
                        // printf("Pressed: %d\n", pressCounter++);
                        rs_gpio_set_irq_with_callback(PIN_KEY_ENTER, GPIO_IRQ_EDGE_RISE, RS_TRUE, &gpio_callback);
                        if(RS_CODE_OK == read_keys(I2C_ID, keyState, &mpKeyboard)){
                            if(streamMode != 0){
                                send_keyboard_state(mpKeyboard);
                            }else{
                                // printf("%#x, %#x, %#x, %#x\n", keyState[0]&0xFF, keyState[1]&0x0F, keyState[2]&0x0E, keyState[3]&0xFF);
                                // printf("\t%#lx\n", mpKeyboard.data.keyMask);
                                print_keyboard_state(debugPrinter, mpKeyboard);
                            }
                        }
                    }
                    //else this was a bounce
                    break;

                case RS_PIN_STATE_LOW:
                    if(gpio_get(PIN_KEY_ENTER) == 1){ // we are now high
                        keyInputState = RS_PIN_STATE_HIGH;
                        // printf("Released: %d\n", releaseCounter++);
                        rs_gpio_set_irq_with_callback(PIN_KEY_ENTER, GPIO_IRQ_EDGE_FALL, RS_TRUE, &gpio_callback);
                    }
                    //else this was a bounce
                    break;
                
            }
        }

        run_task_if_ready(&taskHeartbeat);


        if((newChar > 0) || (taskCLI.counter == 100)){
            cli_process();
            newChar = 0; //still need more atomic way of doing this to be 100% safe
            // print_timestamp(cbTime);
            printf("{\"msg\":");
            while((inputChar = getchar_timeout_us(0)) != PICO_ERROR_TIMEOUT){
                // printf("%c",  inputChar);
                switch(inputChar){
                    case 'r':
                        break;

                    case 's':
                        streamMode ^= 0x1;
                        break;
                    case 'i':
                        printf(" \"build time\", \"value\": \"%s\"", __TIME__);
                        break;

                }
                if (inputChar == 'r'){
                        if(RS_CODE_OK == read_keys(I2C_ID, keyState, &mpKeyboard)){
                            printf(" \"read keys\", \"value\": ");
                            printf("[%#x, %#x, %#x, %#x, ", keyState[0]&0xFF, keyState[1]&0x0F, keyState[2]&0x0E, keyState[3]&0xFF);
                            printf("%#lx]", mpKeyboard.data.keyMask);
                            // print_keyboard_state(debugPrinter, mpKeyboard);
                        }

                }
            }
            printf("}\n");

            if(taskCLI.counter == 0){
                taskCLI.counter = taskCLI.period;
            }
        }

        rs_sleep_ms(1);



        // value = getchar();
        // //printf("Got %c\n", value);
        // blink(1, BLINK_HBT);

        // switch(value){
        //     case 'i':
        //         printf("Built at %s\n", __TIME__);
        //         break;
        //     case 't':
        //         break;
        //     case 'x':
        //         break;
        //     case 'c':
        //         printf("%#x: %d\n", EXP_0, exp_check(I2C_ID, EXP_0));
        //         printf("%#x: %d\n", EXP_1, exp_check(I2C_ID, EXP_1));
        //         printf("%#x: %d\n", EXP_2, exp_check(I2C_ID, EXP_2));
        //         printf("%#x: %d\n", EXP_3, exp_check(I2C_ID, EXP_3));
        //         break;
        //     case '0':
        //         i2cResp.length = 1;
        //         if (rs_i2c_read(I2C_ID, EXP_0, &i2cResp, 0) != RS_CODE_OK){
        //             printf("err addr %x\n", EXP_0);
        //         }else{
        //             printf("%#x: %#x\n", EXP_0, *(i2cResp.data));
        //         }
        //         break;
        //     case '1':
        //         i2cResp.length = 1;
        //         if (rs_i2c_read(I2C_ID, EXP_1, &i2cResp, 0) != RS_CODE_OK){
        //             printf("err addr %x\n", EXP_1);
        //         }else{
        //             printf("%#x: %#x\n", EXP_1, *(i2cResp.data));
        //         }
        //         break;
        //     case '2':
        //         i2cResp.length = 1;
        //         if (rs_i2c_read(I2C_ID, EXP_2, &i2cResp, 0) != RS_CODE_OK){
        //             printf("err addr %x\n", EXP_2);
        //         }else{
        //             printf("%#x: %#x\n", EXP_2, *(i2cResp.data));
        //         }
        //         break;
        //     case '3':
        //         i2cResp.length = 1;
        //         if (rs_i2c_read(I2C_ID, EXP_3, &i2cResp, 0) != RS_CODE_OK){
        //             printf("err addr %x\n", EXP_3);
        //         }else{
        //             printf("%#x: %#x\n", EXP_3, *(i2cResp.data));
        //         }
        //         break;
        //     default:
        //         // printf("\t%#x\n", value);
        //         break;

        // }
    } //end while(true)
}

