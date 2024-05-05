
#include "bsp/led.h"
#include "utils/rs_stdio.h"

#define BLINK_ERROR_TIME 100
#define BLINK_ERROR_COUNT 2

void alert_error();
void print_build_time(void);