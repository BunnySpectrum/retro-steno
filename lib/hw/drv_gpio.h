#ifndef _DRV_GPIO_H_
#define _DRV_GPIO_H_

#include "utils/rs_stdint.h"
#include "utils/rs_stddef.h"
#include "utils/rs_codes.h"

typedef enum{
    RS_GPIO_INPUT = 0,
    RS_GPIO_OUTPUT = 1
}RS_GPIO_DIR_e;

// For now, match pico SDK defines
// enum gpio_function {
//     GPIO_FUNC_XIP = 0,
//     GPIO_FUNC_SPI = 1,
//     GPIO_FUNC_UART = 2,
//     GPIO_FUNC_I2C = 3,
//     GPIO_FUNC_PWM = 4,
//     GPIO_FUNC_SIO = 5,
//     GPIO_FUNC_PIO0 = 6,
//     GPIO_FUNC_PIO1 = 7,
//     GPIO_FUNC_GPCK = 8,
//     GPIO_FUNC_USB = 9,
//     GPIO_FUNC_NULL = 0x1f,
// };
typedef enum{
    RS_GPIO_FUNC_I2C = 3,
    RS_GPIO_FUNC_SIO = 5,
}RS_GPIO_FUNC_e;

// For now, match pico SDK defines
// enum gpio_irq_level {
//     GPIO_IRQ_LEVEL_LOW = 0x1u,
//     GPIO_IRQ_LEVEL_HIGH = 0x2u,
//     GPIO_IRQ_EDGE_FALL = 0x4u,
//     GPIO_IRQ_EDGE_RISE = 0x8u,
// };
typedef enum{
    RS_GPIO_IRQ_EDGE_FALL = 0x4,
}RS_GPIO_IRQ_e;







typedef struct{
    RS_GPIO_DIR_e direction;
    int function;
    RS_BOOL_e value;
} RS_GPIO_Config_s;


RS_CODE_e rs_gpio_init(uint32_t id, const RS_GPIO_Config_s *cfg);
RS_CODE_e rs_gpio_set_direction(uint32_t id, RS_GPIO_DIR_e val);

// True to set, False to clear
RS_CODE_e rs_gpio_put(uint32_t id, RS_BOOL_e val);

// opaque value type to pass to HAL
RS_CODE_e rs_gpio_set_function(uint32_t id, uint32_t val);

RS_CODE_e rs_gpio_set_input_hysteresis(uint32_t id, RS_BOOL_e val);

RS_CODE_e rs_gpio_set_irq_with_callback(uint32_t id, uint32_t eventMask, RS_BOOL_e enable, void (*callback)(unsigned int id, uint32_t eventMask));

RS_CODE_e rs_gpio_pull_up(uint32_t id);
RS_CODE_e rs_gpio_pull_down(uint32_t id);




#endif