#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "utils/rs_stdint.h"
#include "utils/rs_codes.h"


typedef struct{
    void (*task_func)(void);
    volatile int32_t counter;
    int32_t period;
    RS_BOOL_e repeat;
}RS_TASK_INFO_s;

void schedule_task(RS_TASK_INFO_s *taskInfo);
void unschedule_task(RS_TASK_INFO_s *taskInfo);

void run_task_if_ready(RS_TASK_INFO_s *taskInfo);

#endif
