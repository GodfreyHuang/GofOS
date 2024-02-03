#ifndef __TASK_H__
#define __TASK_H__

#include "riscv.h"
#include "switch.h"

#define MAX_TASK 10

extern int taskTop;

extern int task_create(void (*task)(void));
extern void task_switchTask(int i);
extern void task_switchOS();

#endif