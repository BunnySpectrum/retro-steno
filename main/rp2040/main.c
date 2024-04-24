//#include <stdint.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "pico/binary_info.h"

#include "bsp/exp.h"
#include "bsp/bsp.h"
#include "bsp/led.h"
#include "bsp/scheduler.h"
#include "hw/drv_i2c.h"
#include "hw/drv_gpio.h"
#include "bsp/keyboard.h"
#include "utils/rs_time.h"
#include "app/hbt.h"
#include "app/cli.h"



RS_TASK_INFO_s taskHeartbeat = {.task_func = hbt_toggle, .counter = -1, .period = HBT_TASK_PERIOD_MS, .repeat = RS_TRUE};
RS_TASK_INFO_s taskCLI = {.task_func = cli_process, .counter = -1, .period = CLI_TASK_PERIOD_MS, .repeat = RS_FALSE};
RS_TASK_INFO_s taskDebounce = {.task_func = handle_key_debounce, .counter = -1, .period = TASK_KEY_DEBOUNCE_PERIOD_MS, .repeat = RS_FALSE};




// Call this every 1 ms
bool task_period_update_1ms(struct repeating_timer *t){
    if(taskHeartbeat.counter > 0){taskHeartbeat.counter--;}
    if(taskCLI.counter > 0){taskCLI.counter--;}
    if(taskDebounce.counter > 0){taskDebounce.counter--;}

    return true;
}


void char_callback(void* data){
    // *(uint64_t*)data = time_us_64();
    schedule_task(&taskCLI);
}

void gpio_callback(uint gpio, uint32_t events){
    schedule_task(&taskDebounce);
}


extern void (*cmd_cb_info)(void);
extern void (*cmd_cb_stream)(void);
extern void (*cmd_cb_read)(void);


int main() {

    // Set up printer
    Logger_s debugPrinter;
    debugPrinter.printer = &rs_vprintf;

    // Assign callbacks for CLI
    cmd_cb_info = print_build_time;
    cmd_cb_stream = toggle_stream_mode;
    cmd_cb_read = cmd_get_pressed_keys;

    // Init systems
    bsp_gpio_init(gpio_callback);
    bsp_usb_init(&char_callback, NULL);
    bsp_i2c_init(I2C_ID);

    // Make the I2C pins available to picotool
    // TBD how/if to move this out of main
    bi_decl(bi_2pins_with_func(SDA_PIN, SCL_PIN, RS_GPIO_FUNC_I2C));


    // Set up periodic tasks
    hbt_init();
    schedule_task(&taskHeartbeat);

    MPKeyboard_t mpKeyboard;
    keyboard_init(&gpio_callback, debugPrinter, &mpKeyboard, I2C_ID);

    cli_init();

    // Set up timer
    struct repeating_timer timer;
    add_repeating_timer_ms(1, &task_period_update_1ms, NULL, &timer);


    while (true) {

        run_task_if_ready(&taskDebounce);

        run_task_if_ready(&taskHeartbeat);

        run_task_if_ready(&taskCLI);


        rs_sleep_ms(1);


    } 
}

