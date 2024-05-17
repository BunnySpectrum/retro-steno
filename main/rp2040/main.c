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
#include "utils/sys_time.h"
#include "utils/rs_colors.h"
#include "app/hbt.h"
#include "app/cli.h"
#include "app/screen.h"



RS_TASK_INFO_s taskHeartbeat = {.task_func = hbt_toggle, .counter = -1, .period = HBT_TASK_PERIOD_MS, .repeat = RS_TRUE};
RS_TASK_INFO_s taskCLI = {.task_func = cli_process, .counter = -1, .period = CLI_TASK_PERIOD_MS, .repeat = RS_FALSE};
RS_TASK_INFO_s taskDebounce = {.task_func = handle_key_debounce, .counter = -1, .period = TASK_KEY_DEBOUNCE_PERIOD_MS, .repeat = RS_FALSE};
RS_TASK_INFO_s taskScreen = {.task_func = screen_update, .counter = -1, .period = SCREEN_TASK_PERIOD_MS, .repeat = RS_TRUE};




// Call this every 1 ms
bool task_period_update_1ms(struct repeating_timer *t){
    if(taskHeartbeat.counter > 0){taskHeartbeat.counter--;}
    if(taskCLI.counter > 0){taskCLI.counter--;}
    if(taskDebounce.counter > 0){taskDebounce.counter--;}
    if(taskScreen.counter > 0){taskScreen.counter--;}

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
extern void (*cmd_c)(void);
extern void (*cmd_s)(void);

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

    rs_st7735_draw_rect(0, 10, 10, 10, 10, RS_RGB565_WHITE);
    rs_st7735_draw_pixel(0, 15, 15, RS_RGB565_RED);


    printf("\n");
}

void test_time_tick(){
    int32_t tick = (int32_t)to_ms_since_boot(get_absolute_time());
    printf("Tick: %d.\n", tick);
}

void test_u8x8(){

    uint8_t cmdDisplayOff[2] = {0x0, 0xAE};
    uint8_t cmdSetDisplayClockDiv1[2] = {0x0, 0xD5};
    uint8_t cmdSetDisplayClockDiv2[2] = {0x0, 0x80};
    uint8_t cmdSetMultiplex[2] = {0x0, 0xA8};
    uint8_t cmdHeight[2] = {0x0, 31};


    uint8_t cmdDisplayOffset1[2] = {0x0, 0xD3};
    uint8_t cmdDisplayOffset2[2] = {0x0, 0x0};
    uint8_t cmdSetStartline[2] = {0x0, 0x40 | 0x0};
    uint8_t cmdChargepump[2] = {0x0, 0x8D};
    uint8_t cmdVCC1[2] = {0x0, 0x14};
    


    uint8_t cmdMemoryMode1[2] = {0x0, 0x20};
    uint8_t cmdMemoryMode2[2] = {0x0, 0x00};
    uint8_t cmdSegremap[2] = {0x0, 0xA0 | 0x1};
    uint8_t cmdComscandev[2] = {0x0, 0xC8};


    uint8_t comPins = 0x02;
    uint8_t contrast = 0x8F;

    uint8_t cmdSetcompins1[2] = {0x0, 0xDA};
    uint8_t cmdSetcompins2[2] = {0x0, comPins};
    uint8_t cmdSetcontrast1[2] = {0x0, 0x81};
    uint8_t cmdSetcontrast2[2] = {0x0, contrast};
    uint8_t cmdSetprecharge1[2] = {0x0, 0xD9};
    uint8_t cmdSetprecharge2[2] = {0x0, 0xF1};


    uint8_t cmdSetvcomdetect1[2] = {0x0, 0xD8};
    uint8_t cmdSetvcomdetect2[2] = {0x0, 0x40};
    uint8_t cmdDisplayAllOnResume[2] = {0x0, 0xA4};
    uint8_t cmdNormalDisplay[2] = {0x0, 0xA6};
    uint8_t cmdDeactivatescroll[2] = {0x0, 0x2E};
    uint8_t cmdDisplayOn[2] = {0x0, 0xAF};

    uint8_t i2cID = 0;
    uint8_t i2cAddr = 0x3C;
    i2cResponse_t scratch;
    scratch.length = 2;

    scratch.data = cmdDisplayOff;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdSetDisplayClockDiv1;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdSetDisplayClockDiv2;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdSetMultiplex;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdHeight;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);



    // Init 2
    scratch.data = cmdDisplayOffset1;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdDisplayOffset2;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdSetStartline;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdChargepump;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdVCC1;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);


    // Init 3
    scratch.data = cmdMemoryMode1;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdMemoryMode2;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdSegremap;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdComscandev;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);


    // Init 4
    scratch.data = cmdSetcompins1;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdSetcompins2;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdSetcontrast1;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdSetcontrast2;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdSetprecharge1;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdSetprecharge2;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);



    // Init 5
    scratch.data = cmdSetvcomdetect1;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdSetvcomdetect2;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdDisplayAllOnResume;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdNormalDisplay;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdDeactivatescroll;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdDisplayOn;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);


    uint8_t cmdPageaddr1[2] = {0x00, 0x22};
    uint8_t cmdPageaddr2[2] = {0x00, 0x0};
    uint8_t cmdPageaddr3[2] = {0x00, 0xFF};
    uint8_t cmdColumaddr1[2] = {0x00, 0x21};
    uint8_t cmdColumaddr2[2] = {0x00, 0};
    uint8_t cmdWidth[2] = {0x00, 127};

    uint8_t dataPixel1[2] = {0x40, 0xFF};
    uint8_t dataPixel2[2] = {0x40, 0x00};

    scratch.data = cmdPageaddr1;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdPageaddr2;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdPageaddr3;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdColumaddr1;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = cmdColumaddr2;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);
    
    scratch.data = cmdWidth;
    rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    scratch.data = dataPixel1;
    uint8_t row;
    for(int i = 0; i < 128 * ((32+7) / 8); i++){
        row = i / 16;
        if((row % 2) == 0){
            dataPixel1[1] = (i % 2) == 0 ? 0b10101010 : 0b01010101;
        }else{
            dataPixel1[1] = (i % 2) == 0 ? 0b01010101 : 0b10101010;
        }
        rs_i2c_write(i2cID, i2cAddr, &scratch, 0);

    }
}

DISP_CTX_s dispCtx0, dispCtx1;
DISP_CTX_ST7735_s st7735Ctx0, st7735Ctx1;

DISP_CTX_s *displayList[2];

uint16_t debugSeq = 1;
uint16_t newSeq = 1;

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
    cmd_c = test_u8x8;
    cmd_s = i2c_search;

    // Init systems
    bsp_gpio_init(gpio_callback);
    bsp_usb_init(&char_callback, NULL);
    bsp_i2c_init(I2C_ID);
    bsp_spi_init(SPI_ID_DISPLAY);

    // Make the pins available to picotool
    // TBD how/if to move this out of main
    bi_decl(bi_2pins_with_func(SDA_PIN, SCL_PIN, RS_GPIO_FUNC_I2C));
    bi_decl(bi_3pins_with_func(SPI_DISP_MISO_PIN, SPI_DISP_MOSI_PIN, SPI_DISP_SCK_PIN, RS_GPIO_FUNC_SPI));
    bi_decl(bi_1pin_with_name(SPI_DISP0_CS_PIN, "SPI DISP0 CS"));
    bi_decl(bi_1pin_with_name(SPI_DISP1_CS_PIN, "SPI DISP1 CS"));
    bi_decl(bi_1pin_with_name(SPI_DISP0_CARD_CS_PIN, "SPI DISP0 Card CS"));
    bi_decl(bi_1pin_with_name(SPI_DISP1_CARD_CS_PIN, "SPI DISP1 Card CS"));

    // Init display hardware
    displayList[0] = &dispCtx0;
    dispCtx0.objID = 0;
    dispCtx0.driverCtx = &st7735Ctx0;
    
    displayList[1] = &dispCtx1;
    dispCtx1.objID = 1;
    dispCtx1.driverCtx = &st7735Ctx1;

    st7735Ctx0.cardCSPin = SPI_DISP0_CARD_CS_PIN;
    st7735Ctx0.dispDCPin = DISP0_DC_PIN;
    st7735Ctx0.dispCSPin = SPI_DISP0_CS_PIN;
    st7735Ctx0.lightPin = DISP0_LIGHT_PIN;
    st7735Ctx0.resetPin = DISP0_RST_PIN;
    st7735Ctx0.objID = dispCtx0.objID;
    st7735Ctx0.spiID = SPI_ID_DISPLAY;
    st7735Ctx0.colorCoding = 0x5;
    st7735Ctx0.orientation = 0;

    st7735Ctx1.cardCSPin = SPI_DISP1_CARD_CS_PIN;
    st7735Ctx1.dispDCPin = DISP1_DC_PIN;
    st7735Ctx1.dispCSPin = SPI_DISP1_CS_PIN;
    st7735Ctx1.lightPin = DISP1_LIGHT_PIN;
    st7735Ctx1.resetPin = DISP1_RST_PIN;
    st7735Ctx1.objID = dispCtx1.objID;
    st7735Ctx1.spiID = SPI_ID_DISPLAY;
    st7735Ctx1.colorCoding = 0x5;
    st7735Ctx1.orientation = 0;

    bsp_display_init();

    display_init();
    add_displays(displayList, 2);

    screen_init(2);
    schedule_task(&taskScreen);

    // Set up periodic tasks
    hbt_init();
    schedule_task(&taskHeartbeat);

    MPKeyboard_t mpKeyboard;
    keyboard_mp_init(&mpKeyboard, NULL, 0);
    keyboard_init(&gpio_callback, debugPrinter, &mpKeyboard, I2C_ID);

    cli_init();

    // Set up timer
    struct repeating_timer timer;
    add_repeating_timer_ms(1, &task_period_update_1ms, NULL, &timer);


    // display_draw_rect(0, 20, 20, 32, 32, RS_RGB565_MAGENTA);
    // display_draw_rect(1, 20, 20, 32, 32, RS_RGB565_CYAN);

    test_u8x8();

    while (true) {

        run_task_if_ready(&taskDebounce);


        run_task_if_ready(&taskCLI);

        run_task_if_ready(&taskScreen);

        run_task_if_ready(&taskHeartbeat);

        newSeq = mp_get_sequence(mpKeyboard.base);
        if(newSeq > debugSeq ){
            debugSeq = newSeq;

            display_keyboard_callback(&mpKeyboard.base, NULL);
        }

        
        rs_sleep_ms(1);


    } 
}


