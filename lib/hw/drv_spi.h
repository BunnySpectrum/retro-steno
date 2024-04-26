#ifndef _DRV_SPI_H_
#define _DRV_SPI_H_

#include "utils/rs_stdint.h"
#include "utils/rs_stddef.h"
#include "utils/rs_codes.h"

typedef struct spiResponse{
    RS_CODE_e rc;
    uint8_t* data;
    uint32_t length;

} spiResponse_t;


RS_CODE_e rs_spi_init(uint8_t id, uint32_t speed);
RS_CODE_e rs_spi_mode(spiResponse_t *resp, uint8_t id, unsigned int bits, RS_BOOL_e polarity, RS_BOOL_e phase, RS_BOOL_e msbFirst);

RS_CODE_e rs_spi_send_data(spiResponse_t *resp, uint8_t id);
RS_CODE_e rs_spi_recv_data(spiResponse_t *resp, uint8_t id, uint8_t txData);





#endif