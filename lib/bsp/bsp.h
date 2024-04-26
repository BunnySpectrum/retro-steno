#ifndef _BSP_H_
#define _BSP_H_

#include "hw/drv_gpio.h"
#include "hw/drv_i2c.h"
#include "hw/drv_spi.h"
#include "bsp/pinmap.h"
#include "app/alert.h"
#include "utils/rs_codes.h"

RS_CODE_e bsp_gpio_init(void (*gpio_callback)(unsigned int, uint32_t));
RS_CODE_e bsp_usb_init(void (*char_callback)(void* data), uint64_t *cbTime);
RS_CODE_e bsp_i2c_init(uint32_t i2cID);
RS_BOOL_e bsp_spi_init(uint32_t spiID);
RS_BOOL_e bsp_display_init();

#endif
