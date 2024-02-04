#ifndef __OS_H__
#define __OS_H__

#include "lib.h"
#include "riscv.h"
#include "task.h"

extern void user_init();
extern void os_init();

//trap
extern void trap_init(void);
extern void os_switch();

// memory allocator
extern void *malloc(size_t size);
extern void free(void *p);
extern void page_init();
extern void page_test();

#endif