#ifndef _CLI_H_
#define _CLI_H_

#include "utils/rs_codes.h"
#include "utils/rs_stdio.h"

#define CLI_TASK_PERIOD_MS 5

extern volatile char newChar;

void cli_init();
void cli_process();


#endif
