#ifndef __LIB_H__
#define __LIB_H__

#include <stdarg.h>
#include <stddef.h>
#include "riscv.h"

// string functions
extern char *gets(char *);
extern int getc(void);
extern int putc(char ch);
extern void puts(char *s);

// printf functions
extern void printf(const char *s, ...);
extern void vprintf(va_list ap, const char *fmt);

// timer
extern void delay(volatile int num);

extern void sys_counter();
extern uint32_t timer_oneSecondCounter(uint32_t epc, uint32_t cause);
extern void timer_oneSecondClock();

extern void sys_timer();
extern void timer_handler();
extern void timer_init();

// PLIC
extern void isr();

#endif