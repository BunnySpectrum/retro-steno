//#include <stdint.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "pico/binary_info.h"

#include "bsp/exp.h"
#include "bsp/bsp.h"
#include "bsp/led.h"
#include "bsp/scheduler.h"
#include "bsp/display.h"
#include "hw/drv_i2c.h"
#include "hw/drv_gpio.h"
#include "bsp/keyboard.h"
#include "utils/rs_time.h"
#include "utils/rs_colors.h"
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
extern void (*cmd_a)(void);
extern void (*cmd_b)(void);

#include "hardware/spi.h"
void test_disp_spi(){
    printf("Test spi:\n");
    spiResponse_t resp1, resp2;
    uint8_t data1[2] = {0xDA, 0x00};
    uint8_t data2[2] = {0x00, 0x00};


    // rs_gpio_put(SPI_DISP_CS_PIN, 0);
    // spi_write_read_blocking(spi1, data1, data2, 2);
    // rs_gpio_put(SPI_DISP_CS_PIN, 1);

    // rs_gpio_put(DISP_DC_PIN, 0);
    // resp1.data = data1;
    // resp1.length = 1;
    // rs_spi_send_data(&resp1, SPI_ID_DISPLAY);
    // printf("Read reg rc: %d\n", resp1.rc);

    // resp2.data = data2;
    // resp2.length = 1;
    // rs_gpio_put(DISP_DC_PIN, 1);
    // rs_spi_recv_data(&resp2, SPI_ID_DISPLAY, 0x0);
    // rs_gpio_put(DISP_DC_PIN, 0);
    // printf("Read ID: rc = %d, data = %d\n", resp2.rc, resp2.data[0]);

    rs_st7735_fill_rect(0, 10, 10, 10, 10, RS_RGB565_WHITE);
    rs_st7735_set_pixel(0, 15, 15, RS_RGB565_RED);


    printf("\n");
}

void test_time_tick(){
    int32_t tick = (int32_t)to_ms_since_boot(get_absolute_time());
    printf("Tick: %d.\n", tick);
}

int main() {

    // Set up printer
    Logger_s debugPrinter;
    debugPrinter.printer = &rs_vprintf;
    set_logger_display(debugPrinter);

    // Assign callbacks for CLI
    cmd_cb_info = print_build_time;
    cmd_cb_stream = toggle_stream_mode;
    cmd_cb_read = cmd_get_pressed_keys;
    cmd_a = test_disp_spi;
    cmd_b = test_time_tick;

    // Init systems
    bsp_gpio_init(gpio_callback);
    bsp_usb_init(&char_callback, NULL);
    bsp_i2c_init(I2C_ID);
    bsp_spi_init(SPI_ID_DISPLAY);

    // Make the pins available to picotool
    // TBD how/if to move this out of main
    bi_decl(bi_2pins_with_func(SDA_PIN, SCL_PIN, RS_GPIO_FUNC_I2C));
    bi_decl(bi_3pins_with_func(SPI_DISP_MISO_PIN, SPI_DISP_MOSI_PIN, SPI_DISP_SCK_PIN, RS_GPIO_FUNC_SPI));
    bi_decl(bi_1pin_with_name(SPI_DISP_CARD_CS_PIN, "SPI DISP CS"));

    // Init display hardware
    bsp_display_init();

    // display_init(SPI_ID_DISPLAY);
    display_reset();

    // Set up periodic tasks
    hbt_init();
    schedule_task(&taskHeartbeat);

    MPKeyboard_t mpKeyboard;
    keyboard_init(&gpio_callback, debugPrinter, &mpKeyboard, I2C_ID);

    cli_init();

    // Set up timer
    struct repeating_timer timer;
    add_repeating_timer_ms(1, &task_period_update_1ms, NULL, &timer);


    display_init(SPI_ID_DISPLAY, 0);

    while (true) {

        run_task_if_ready(&taskDebounce);

        run_task_if_ready(&taskHeartbeat);

        run_task_if_ready(&taskCLI);


        rs_sleep_ms(1);


    } 
}

