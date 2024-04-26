#include "hw/drv_spi.h"

//pico SDK
#include "hardware/spi.h"



#define SPI_INSTANCE_COUNT 2
static spi_inst_t *spi_instances[SPI_INSTANCE_COUNT] = {spi0, spi1};

RS_CODE_e rs_spi_init(uint8_t id, uint32_t speed){
    uint32_t actualSpeed;

    if (id > SPI_INSTANCE_COUNT-1){
        return RS_CODE_ERR;
    }

    actualSpeed = spi_init(spi_instances[id], speed);
    return actualSpeed == speed ? RS_CODE_OK : RS_CODE_ERR;
}

RS_CODE_e rs_spi_mode(spiResponse_t *resp, uint8_t id, unsigned int bits, RS_BOOL_e polarity, RS_BOOL_e phase, RS_BOOL_e msbFirst){
    resp->rc = RS_CODE_ERR;

    if (id > SPI_INSTANCE_COUNT-1){
        return resp->rc;
    }
    spi_set_format(spi_instances[id], bits, polarity, phase, 1);

    return resp->rc;
}

RS_CODE_e rs_spi_send_data(spiResponse_t *resp, uint8_t id){
    resp->rc = RS_CODE_ERR;
    if (id > SPI_INSTANCE_COUNT-1){
        return resp->rc;
    }

    if(resp->length == spi_write_blocking(spi_instances[id], resp->data, resp->length)){
        resp->rc = RS_CODE_OK;
    }

    return resp->rc;

}

RS_CODE_e rs_spi_recv_data(spiResponse_t *resp, uint8_t id, uint8_t txData){
    resp->rc = RS_CODE_ERR;
    if (id > SPI_INSTANCE_COUNT-1){
        return resp->rc;
    }
    
    if(resp->length == spi_read_blocking(spi_instances[id], txData, resp->data, resp->length)){
        resp->rc = RS_CODE_OK;
    }

    return resp->rc;
}