#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "display.h"

static Logger_s displayPrinter;
static uint8_t displayID;

int32_t rs_st7735_init(){
    return 1;
}

int32_t rs_st7735_deinit(){
    return 2;
}

int32_t rs_st7735_writereg(uint8_t reg, uint8_t *data, uint32_t length){
    spiResponse_t resp1, resp2;
    uint8_t data1[1] = {reg};
    resp1.data = data1;
    resp1.length = 1;

    rs_gpio_put(DISP_DC_PIN, 0);
    rs_gpio_put(SPI_DISP_CS_PIN, 0);
    rs_spi_send_data(&resp1, displayID);
    rs_gpio_put(SPI_DISP_CS_PIN, 1);
    
    if(length > 0){
        resp2.data = data;
        resp2.length = length;

        rs_gpio_put(DISP_DC_PIN, 1);
        rs_gpio_put(SPI_DISP_CS_PIN, 0);
        rs_spi_send_data(&resp2, displayID);
        rs_gpio_put(SPI_DISP_CS_PIN, 1);
    }

    // rs_log(displayPrinter, "Write reg: reg %#x\n", reg);
    return resp2.length;
}

int32_t rs_st7735_readreg(uint8_t reg, uint8_t *data){
    spiResponse_t resp1, resp2;
    uint8_t data1[2] = {reg, 0x0};
    uint8_t data2[2] = {0x0, 0x0};
    resp1.data = data1;
    resp1.length = 1;

    resp2.data = data2;
    resp2.length = 1;



    rs_gpio_put(DISP_DC_PIN, 0);
    rs_gpio_put(SPI_DISP_CS_PIN, 0);
    rs_spi_send_data(&resp1, displayID);
    rs_spi_recv_data(&resp2, displayID, 0x0);
    rs_gpio_put(SPI_DISP_CS_PIN, 1);

    *data = resp2.data[0];

    rs_log(displayPrinter, "Read reg: reg %#x, data %#d\n", reg, resp2.data[0]);
    return 4;
}

int32_t rs_st7735_senddata(uint8_t *data, uint32_t length){
    spiResponse_t resp2;

    resp2.data = data;
    resp2.length = length;

    rs_gpio_put(DISP_DC_PIN, 1);
    rs_gpio_put(SPI_DISP_CS_PIN, 0);
    rs_spi_send_data(&resp2, displayID);
    rs_gpio_put(SPI_DISP_CS_PIN, 1);


    // rs_log(displayPrinter, "Send data: data[0] %#x, length %d.\n", data[0], length);
    return resp2.length;
}

int32_t rs_st7735_recvdata(uint8_t *data, uint32_t length){
    return 6;
}

int32_t rs_st7735_gettick(){
    return to_ms_since_boot(get_absolute_time());
}

void set_logger_display(Logger_s printer){
    displayPrinter = printer;
}

void display_reset(){
    rs_gpio_put(DISP_RST_PIN, RS_FALSE);
    sleep_ms(100);
    rs_gpio_put(DISP_RST_PIN, RS_TRUE);
}

void rs_st7735_setwindow(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1){
    uint8_t xStart[2] = {x0>>8, x0 & 0xFF};
    uint8_t xEnd[2] = {x1>>8, x1 & 0xFF};
    uint8_t yStart[2] = {y0>>8, y0 & 0xFF};
    uint8_t yEnd[2] = {y1>>8, y1 & 0xFF};


    rs_st7735_writereg(ST7735_CASET, NULL, 0);
    rs_st7735_senddata(xStart, 2);
    rs_st7735_senddata(xEnd, 2);

    rs_st7735_writereg(ST7735_RASET, NULL, 0);
    rs_st7735_senddata(yStart, 2);
    rs_st7735_senddata(yEnd, 2);
}

void rs_st7735_setpixel(uint32_t xPos, uint32_t yPos, uint32_t color){

}

#define DISP_WIDTH 130
#define DISP_HEIGHT 132

void display_init(uint8_t spiID){
    ST7735_Object_t obj;
    ST7735_IO_t io;

    displayID = spiID;

    io.Init = rs_st7735_init; 
    io.DeInit = rs_st7735_deinit;
    io.Address = 1;
    io.WriteReg = rs_st7735_writereg;
    io.ReadReg = rs_st7735_readreg;
    io.SendData = rs_st7735_senddata;
    io.RecvData = rs_st7735_recvdata;
    io.GetTick = rs_st7735_gettick;


    int32_t result;
    result = ST7735_RegisterBusIO(&obj, &io);
    rs_log(displayPrinter, "Register bus io: %d.\n", result);

    // uint8_t data = 0x0;
    // rs_log(displayPrinter, "Sleep out: %d.\n", result);

    // ST7735_Init(&obj, 0x5, 0);
    rs_st7735_writereg(ST7735_SW_RESET, NULL, 0);
    sleep_ms(150);

    rs_st7735_writereg(ST7735_SLEEP_OUT, NULL, 0);
    sleep_ms(200);

    uint8_t data = 5;
    rs_st7735_writereg(ST7735_COLOR_MODE, &data, 1);
    sleep_ms(10);

    data = 0x00;
    rs_st7735_writereg(ST7735_MADCTL, &data, 1);
    sleep_ms(10);

    rs_st7735_writereg(ST7735_DISPLAY_ON, NULL, 0);
    sleep_ms(200);

    // ST7735_SetOrientation(&obj, 0);

    // set window: 0, width, 0, height
    uint8_t data0[2] = {0x00, 0x00};
    uint8_t red[2] = {0x00, 0xF0};
    uint8_t blue[2] = {0xF0, 0x00};
    uint8_t white[2] = {0xFF, 0xFF};
    uint8_t width[2] = {0x00, DISP_WIDTH};
    uint8_t height[2] = {0x00, DISP_HEIGHT};
    // rs_st7735_writereg(ST7735_CASET, NULL, 0);
    // rs_st7735_senddata(data0, 2);
    // rs_st7735_senddata(width, 2);

    // rs_st7735_writereg(ST7735_RASET, NULL, 0);
    // data0[0] = 0;
    // data0[1] = 0;
    // rs_st7735_senddata(data0, 2);
    // rs_st7735_senddata(height, 2);

    uint32_t count;
    // Draw black pixels
    // rs_st7735_writereg(ST7735_WRITE_RAM, NULL, 0);
    // count = DISP_WIDTH * DISP_HEIGHT;
    // while(count--){
    //     rs_st7735_senddata(red, 2);
    // }

    // result = ST7735_SetCursor(&obj, 0, 0);
    // rs_log(displayPrinter, "Set cursor (0,0): %d", result);

    rs_st7735_setwindow(0, DISP_WIDTH, 0, DISP_HEIGHT);
    rs_st7735_writereg(ST7735_WRITE_RAM, NULL, 0);
    count = DISP_HEIGHT*DISP_WIDTH;
    while(count--){
        rs_st7735_senddata(blue, 2);
    }

    // sleep_ms(200);
    uint8_t pixel;

    pixel = 5;
    rs_st7735_setwindow(pixel, pixel, pixel, pixel);
    rs_st7735_writereg(ST7735_WRITE_RAM, NULL, 0);
    count = 1;
    while(count--){
        rs_st7735_senddata(white, 2);
    }

    pixel = 10;
    rs_st7735_setwindow(pixel, pixel, pixel, pixel);
    rs_st7735_writereg(ST7735_WRITE_RAM, NULL, 0);
    count = 1;
    while(count--){
        rs_st7735_senddata(white, 2);
    }
    
    pixel = 128;
    rs_st7735_setwindow(129, 129, 128, 128);
    rs_st7735_writereg(ST7735_WRITE_RAM, NULL, 0);
    count = 1;
    while(count--){
        rs_st7735_senddata(white, 2);
    }
    
    // lower right
    rs_st7735_setwindow(2, 2, 1, 1);
    rs_st7735_writereg(ST7735_WRITE_RAM, NULL, 0);
    count = 1;
    while(count--){
        rs_st7735_senddata(white, 2);
    }

    rs_st7735_setwindow(2, 2, 128, 128);
    rs_st7735_writereg(ST7735_WRITE_RAM, NULL, 0);
    count = 1;
    while(count--){
        rs_st7735_senddata(white, 2);
    }

    rs_st7735_setwindow(129, 129, 1, 1);
    rs_st7735_writereg(ST7735_WRITE_RAM, NULL, 0);
    count = 1;
    while(count--){
        rs_st7735_senddata(white, 2);
    }




    rs_st7735_setwindow(10, 100, 10, 10);
    rs_st7735_writereg(ST7735_WRITE_RAM, NULL, 0);
    count = 45;
    while(count--){
        rs_st7735_senddata(red, 2);
    }

    rs_st7735_setwindow(10, 100, 100, 100);
    rs_st7735_writereg(ST7735_WRITE_RAM, NULL, 0);
    count = 45;
    while(count--){
        rs_st7735_senddata(red, 2);
    }
    // result = ST7735_FillRect(&obj, 0, 0, ST7735_WIDTH, ST7735_HEIGHT, 0xFFFF);
    // rs_log(displayPrinter, "Fill rect: %d", result);

    // result = ST7735_DrawHLine(&obj, 0, 0, 127, 0xF000);
    // rs_log(displayPrinter, "HLine: %d", result);
    // // ST7735_DrawHLine(&obj, 0, 127, 127, 0xFFFF);


    rs_log(displayPrinter, "Init done");

    // sleep_ms(100);

    // ST7735_DisplayOn(&obj);
    // sleep_ms(100);

    // ST7735_SetCursor(&obj, 0, 0);
    // sleep_ms(100);

    // ST7735_SetPixel(&obj, 20, 20, 0x0);
    // ST7735_FillRect(&obj, 0, 0, ST7735_WIDTH, ST7735_HEIGHT, 0x0000);

    // sleep_ms(100);

}



#endif
