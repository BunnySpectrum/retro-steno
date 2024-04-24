#ifndef _CLI_H_
#define _CLI_H_


#define CLI_TASK_PERIOD_MS 10

extern volatile char newChar;

void cli_init();
void cli_process();


#endif
