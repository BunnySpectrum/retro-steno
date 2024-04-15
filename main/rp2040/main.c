//#include <stdint.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "pico/binary_info.h"

#include "bsp/exp.h"
#include "hw/drv_i2c.h"
#include "bsp/keyboard.h"

#define BLINK_LONG 500
#define BLINK_HBT 10
#define BLINK_FAST 100

#define LED_PIN 13
#define SDA_PIN 16
#define SCL_PIN 17
#define PIN_KEY_ENTER 12

#define I2C_ID 0

#define HBT_TASK_PERIOD_MS 200
#define INPUT_TASK_PERIOD_MS 10
#define TASK_KEY_DEBOUNCE_PERIOD_MS 25

uint8_t hbtState = 0;
volatile uint16_t taskPeriodHeartbeat = HBT_TASK_PERIOD_MS;
volatile uint16_t taskPeriodInput = INPUT_TASK_PERIOD_MS;
volatile int16_t taskKeyDebounce = -1;

volatile uint64_t lastTimestamp = 0;

void hbt_toggle(){
    gpio_put(LED_PIN, hbtState);
    hbtState ^= 0x1;
}

// Call this every 1 ms
bool task_period_update_1ms(struct repeating_timer *t){
    if(taskPeriodHeartbeat > 0){taskPeriodHeartbeat--;}
    if(taskPeriodInput > 0){taskPeriodInput--;}
    if(taskKeyDebounce > 0){taskKeyDebounce--;}

    return true;
}

void print_timestamp(uint64_t timestamp){
    uint64_t sec, msec, usec;

    sec = timestamp/1e6;
    msec = (timestamp/1e3) - sec*1e3;
    usec = timestamp- sec*1e6 - msec*1e3;

    printf("Time (s, ms, us): %lld, %lld, %lld\n", sec, msec, usec);
    return;
}

bool timer_callback_test(struct repeating_timer *t){
    uint64_t timestamp = time_us_64();
    uint64_t delta = timestamp - lastTimestamp;
    uint64_t sec, msec, usec;

    sec = delta/1e6;
    msec = (delta/1e3) - sec*1e3;
    usec = delta- sec*1e6 - msec*1e3;

    printf("Time (s, ms, us): %lld, %lld, %lld\n", sec, msec, usec);
    lastTimestamp = timestamp;
    return true;
}

void blink(uint8_t count, uint16_t delay){
    for(uint8_t i=0; i<count; i++){
        gpio_put(LED_PIN, 1);
        sleep_ms(delay);
        gpio_put(LED_PIN, 0);
        sleep_ms(delay);
    }
}

volatile bool newChar = 0;
uint64_t cbTime = 0;

void char_callback(void* data){
    newChar = 1;
    *(uint64_t*)data = time_us_64();
}

void gpio_callback(uint gpio, uint32_t events){
    taskKeyDebounce = TASK_KEY_DEBOUNCE_PERIOD_MS;
    // printf("GPIO %d %#x\n", gpio, events);
}

void bsp_gpio_init(void){
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(PIN_KEY_ENTER);
    gpio_set_dir(PIN_KEY_ENTER, GPIO_IN);
    gpio_set_input_hysteresis_enabled(PIN_KEY_ENTER, true);
    gpio_set_irq_enabled_with_callback(PIN_KEY_ENTER, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

}

typedef enum PinInputFSM{
    RS_PIN_STATE_HIGH = 0,
    RS_PIN_STATE_FALL = 1,
    RS_PIN_STATE_LOW = 2,
    RS_PIN_STATE_RISE = 3
} PinInputFSM_e;


RSCode_e read_keys(uint8_t* keys, MPKeyboard_t* mp){
    uint8_t i2cData;

    i2cResponse_t scratch;
    scratch.length = 1;
    scratch.data = &i2cData;

    keys[0] = 0;
    keys[1] = 0;
    keys[2] = 0;
    keys[3] = 0;

    if (rs_i2c_read(I2C_ID, EXP_0, &scratch, 0) != RS_CODE_OK){
        printf("err addr %x\n", EXP_0);
        return RS_CODE_ERR;
    }else{
        keys[0] = *(scratch.data);
    }

    if (rs_i2c_read(I2C_ID, EXP_1, &scratch, 0) != RS_CODE_OK){
        printf("err addr %x\n", EXP_1);
        return RS_CODE_ERR;
    }else{
        keys[1] = *(scratch.data);
        // data |= (uint32_t)(*(scratch.data)) << 8;
    }

    if (rs_i2c_read(I2C_ID, EXP_2, &scratch, 0) != RS_CODE_OK){
        printf("err addr %x\n", EXP_2);
        return RS_CODE_ERR;
    }else{
        keys[2] = *(scratch.data);
        // data |= (uint32_t)(*(scratch.data)) << 16;
    }

    if (rs_i2c_read(I2C_ID, EXP_3, &scratch, 0) != RS_CODE_OK){
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

    bsp_gpio_init();

    flag = stdio_usb_init();
    stdio_set_chars_available_callback(&char_callback, &cbTime);

    if(flag == 0){
        // failed to setup CDC
        blink(2, BLINK_FAST);
    }else{
        // success
        blink(5, BLINK_FAST);
    }

    if(rs_i2c_init(I2C_ID, 100 * 1000) != RS_CODE_OK){
        printf("Error enabling i2c %d", I2C_ID);
        blink(10, BLINK_FAST);
    };

    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(SDA_PIN, SCL_PIN, GPIO_FUNC_I2C));


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
                        gpio_set_irq_enabled_with_callback(PIN_KEY_ENTER, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
                        if(RS_CODE_OK == read_keys(keyState, &mpKeyboard)){
                            if(streamMode != 0){
                                send_keyboard_state(mpKeyboard);
                            }else{
                                printf("%#x, %#x, %#x, %#x\n", keyState[0]&0xFF, keyState[1]&0x0F, keyState[2]&0x0E, keyState[3]&0xFF);
                                printf("\t%#lx\n", mpKeyboard.data.keyMask);
                                print_keyboard_state(mpKeyboard);
                            }
                        }
                    }
                    //else this was a bounce
                    break;

                case RS_PIN_STATE_LOW:
                    if(gpio_get(PIN_KEY_ENTER) == 1){ // we are now high
                        keyInputState = RS_PIN_STATE_HIGH;
                        // printf("Released: %d\n", releaseCounter++);
                        gpio_set_irq_enabled_with_callback(PIN_KEY_ENTER, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
                    }
                    //else this was a bounce
                    break;
                
            }
        }

        if(taskPeriodHeartbeat == 0){
            hbt_toggle();
            taskPeriodHeartbeat = HBT_TASK_PERIOD_MS;
        }


        if((newChar > 0) || (taskPeriodInput == 100)){
            newChar = 0; //still need more atomic way of doing this to be 100% safe
            // print_timestamp(cbTime);
            printf("{msg:'");
            while((inputChar = getchar_timeout_us(0)) != PICO_ERROR_TIMEOUT){
                printf("%c",  inputChar);
                switch(inputChar){
                    case 'r':
                        break;

                    case 's':
                        streamMode ^= 0x1;
                        break;
                    case 'i':
                        printf("info\n");
                        rs_printf("\ttest\n");
                        break;

                }
                if (inputChar == 'r'){
                        if(RS_CODE_OK == read_keys(keyState, &mpKeyboard)){
                            printf("%#x, %#x, %#x, %#x\n", keyState[0]&0xFF, keyState[1]&0x0F, keyState[2]&0x0E, keyState[3]&0xFF);
                            printf("\t%#lx\n", mpKeyboard.data.keyMask);
                            print_keyboard_state(mpKeyboard);
                        }

                }
            }
            printf("'}\n");

            if(taskPeriodInput == 0){
                taskPeriodInput = INPUT_TASK_PERIOD_MS;
            }
        }

        sleep_ms(1);



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

