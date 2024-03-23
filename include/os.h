#ifndef __OS_H__
#define __OS_H__

#include "lib.h"
#include "riscv.h"
#include "task.h"

extern void user_init();
extern void os_init();

// trap
extern void trap_init(void);
extern void os_switch();

// PLIC
extern void plic_init();
extern int plic_claim();
extern void plic_complete(int);

// memory allocator
extern void *malloc(size_t size);
extern void free(void *p);
extern void page_init();
extern void page_test();

// lock
typedef struct lock
{
    volatile int locked;
} lock_t;

extern void basic_lock();
extern void basic_unlock();
extern void lock_init(lock_t *l);
extern void lock_free(lock_t *l);
extern void lock_acquire(lock_t *l);
extern int atomic_swap(lock_t *);

#endif