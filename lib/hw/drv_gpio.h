#ifndef _DRV_GPIO_H_
#define _DRV_GPIO_H_

#include "utils/rs_stdint.h"
#include "utils/rs_stddef.h"
#include "utils/rs_codes.h"

typedef enum{
    RS_GPIO_INPUT = 0,
    RS_GPIO_OUTPUT = 1
}RS_GPIO_DIR_e;


typedef struct{
    RS_GPIO_DIR_e direction;
    int function;
    RS_BOOL_e value;
} RS_GPIO_Config_s;


RSCode_e rs_gpio_init(uint32_t id, const RS_GPIO_Config_s *cfg);
RSCode_e rs_gpio_set_direction(uint32_t id, RS_GPIO_DIR_e val);

// True to set, False to clear
RSCode_e rs_gpio_put(uint32_t id, RS_BOOL_e val);

// opaque value type to pass to HAL
RSCode_e rs_gpio_set_function(uint32_t id, uint32_t val);

RSCode_e rs_gpio_set_input_hysteresis(uint32_t id, RS_BOOL_e val);

RSCode_e rs_gpio_set_irq_with_callback(uint32_t id, uint32_t eventMask, RS_BOOL_e enable, void (*callback)(unsigned int id, uint32_t eventMask));

RSCode_e rs_gpio_pull_up(uint32_t id);
RSCode_e rs_gpio_pull_down(uint32_t id);




#endif