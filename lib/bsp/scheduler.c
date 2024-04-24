#include "scheduler.h"

void schedule_task(RS_TASK_INFO_s *taskInfo){
    taskInfo->counter = taskInfo->period;
}

void unschedule_task(RS_TASK_INFO_s *taskInfo){
    taskInfo->counter = -1;
}

void run_task_if_ready(RS_TASK_INFO_s *taskInfo){
    if(taskInfo->counter == 0){
        taskInfo->task_func();
        taskInfo->counter = taskInfo->repeat == RS_TRUE ? taskInfo->period : -1;
    }
}