#include "st7735_reg.h"
#include "st7735.h"

#include "utils/rs_stdio.h"
#include "hw/drv_spi.h"
#include "hw/drv_gpio.h"
#include "bsp/pinmap.h"

#include "pico/time.h"

void display_init(uint8_t spiID);
void set_logger_display(Logger_s printer);
void display_reset();