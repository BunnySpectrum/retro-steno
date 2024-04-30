#include "hw/drv_st7735.h"

#include "st7735.h"
#include "st7735_reg.h"

static uint8_t SPI_ID_ST7735;
static ST7735_Object_t driverObjects[MAX_NUM_DISPLAY_DRIVERS];
static ST7735_IO_t driverIOs[MAX_NUM_DISPLAY_DRIVERS];

int32_t rs_st7735_writereg(uint8_t reg, uint8_t *data, uint32_t length){
    spiResponse_t resp1, resp2;
    uint8_t data1[1] = {reg};
    resp1.data = data1;
    resp1.length = 1;

    rs_gpio_put(DISP_DC_PIN, 0);
    rs_gpio_put(SPI_DISP_CS_PIN, 0);
    rs_spi_send_data(&resp1, SPI_ID_DISPLAY);
    rs_gpio_put(SPI_DISP_CS_PIN, 1);
    
    if(length > 0){
        resp2.data = data;
        resp2.length = length;

        rs_gpio_put(DISP_DC_PIN, 1);
        rs_gpio_put(SPI_DISP_CS_PIN, 0);
        rs_spi_send_data(&resp2, SPI_ID_DISPLAY);
        rs_gpio_put(SPI_DISP_CS_PIN, 1);
    }

    return ST7735_OK;
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
    rs_spi_send_data(&resp1, SPI_ID_DISPLAY);
    rs_spi_recv_data(&resp2, SPI_ID_DISPLAY, 0x0);
    rs_gpio_put(SPI_DISP_CS_PIN, 1);

    *data = resp2.data[0];

    return ST7735_OK;
}

int32_t rs_st7735_senddata(uint8_t *data, uint32_t length){
    spiResponse_t resp2;

    resp2.data = data;
    resp2.length = length;

    rs_gpio_put(DISP_DC_PIN, 1);
    rs_gpio_put(SPI_DISP_CS_PIN, 0);
    rs_spi_send_data(&resp2, SPI_ID_DISPLAY);
    rs_gpio_put(SPI_DISP_CS_PIN, 1);


    return ST7735_OK;
}

int32_t rs_st7735_recvdata(uint8_t *data, uint32_t length){
    return ST7735_ERROR;
}

int32_t rs_st7735_gettick(){
    return to_ms_since_boot(get_absolute_time());
}



int32_t rs_st7735_io_init(){
    return ST7735_OK;
}

int32_t rs_st7735_io_deinit(){
    return ST7735_OK;
}

RS_CODE_e rs_st7735_init(uint8_t spiID, uint8_t driverID){
    if (driverID >= MAX_NUM_DISPLAY_DRIVERS){
        return RS_CODE_ERR;
    }
    ST7735_Object_t *obj = &driverObjects[driverID];
    ST7735_IO_t *io = &driverIOs[driverID];


    io->Init = rs_st7735_io_init; 
    io->DeInit = rs_st7735_io_deinit;
    io->Address = driverID;
    io->WriteReg = rs_st7735_writereg;
    io->ReadReg = rs_st7735_readreg;
    io->SendData = rs_st7735_senddata;
    io->RecvData = rs_st7735_recvdata;
    io->GetTick = rs_st7735_gettick;



    int32_t result;
    /**
     * N.B. This method doesn't allow for multiple drivers. Need to address that in a later change
     * Need to make the ctx read/write methods point to something that uses handle -> Object -> IO -> address
     * But then that would mean we couldn't use the IO.read/write methods since those signatures don't account for address
     * Unless you make different wrapping methods for read/write per instance....but that doesn't feel right
    */
    result = ST7735_RegisterBusIO(obj, io);


    ST7735_Init(obj, 0x5, 0);


    uint32_t count;

    // fill full RAM with black
    ST7735_FillRect(obj, 0, 0, ST7735_WIDTH, ST7735_HEIGHT, RS_RGB565_BLACK);

    // sleep_ms(200);
    uint8_t pixel;




}

RS_CODE_e rs_st7735_set_pixel(uint8_t driverID, uint32_t x, uint32_t y, RS_RGB565_e color){
    if(driverID >= MAX_NUM_DISPLAY_DRIVERS){
        return RS_CODE_ERR;
    }

    ST7735_SetPixel(&driverObjects[driverID], x, y, color);
    // ST7735_SetPixel(&obj, x, y, color);
    return RS_CODE_OK;
}


RS_CODE_e rs_st7735_fill_rect(uint8_t driverID, uint32_t x, uint32_t y, uint32_t width, uint32_t height, RS_RGB565_e color){
    if(driverID >= MAX_NUM_DISPLAY_DRIVERS){
        return RS_CODE_ERR;
    }

    ST7735_FillRect(&driverObjects[driverID], x, y, width, height, color);
    // ST7735_FillRect(&obj, x, y, width, height, color);
    return RS_CODE_OK;
}

