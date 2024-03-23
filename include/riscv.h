#ifndef __RISCV_H__
#define __RISCV_H__

#include <stdint.h>
#include <stdlib.h>

#include "memlayout.h"
#include "uart.h"

// ref: https://github.com/mit-pdos/xv6-riscv/blob/riscv/kernel/riscv.h

static inline uint32_t r_tp()
{
  uint32_t x;
  asm volatile("mv %0, tp"
               : "=r"(x));
  return x;
}

// which hart (core) is this?
static inline uint32_t r_mhartid()
{
    uint32_t x = 0;
    asm volatile("csrr %0, mhartid" : "=r"(x));
    return x;
}

// Machine Status Register, mstatus
#define MSTATUS_MPP_MASK (3L << 11)  // previous mode.
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)
#define MSTATUS_MIE (1L << 3)  // machine-mode interrupt enable.

static inline uint32_t r_mstatus()
{
    uint32_t x = 0;
    asm volatile("csrr %0, mstatus" : "=r"(x));
    return x;
}

static inline void w_mstatus(uint32_t x)
{
    asm volatile("csrw mstatus, %0" : : "r"(x));
}

// machine exception program counter, holds the
// instruction address to which a return from
// exception will go.
static inline void w_mepc(uint32_t x)
{
    asm volatile("csrw mepc, %0" : : "r"(x));
}

static inline uint32_t r_mepc()
{
    uint32_t x = 0;
    asm volatile("csrr %0, mepc" : "=r"(x));
    return x;
}

// Machine Scratch register, for early trap handler
static inline void w_mscratch(uint32_t x)
{
    asm volatile("csrw mscratch, %0" : : "r"(x));
}

// Machine-mode interrupt vector
static inline void w_mtvec(uint32_t x)
{
    asm volatile("csrw mtvec, %0" : : "r"(x));
}

// Machine-mode Interrupt Enable
// Machine-mode Interrupt Enable
#define MIE_MEIE (1L << 11)  // external
#define MIE_MTIE (1L << 7)   // timer
#define MIE_MSIE (1L << 3)   // software
static inline uint32_t r_mie()
{
    uint32_t x = 0;
    asm volatile("csrr %0, mie" : "=r"(x));
    return x;
}

static inline void w_mie(uint32_t x)
{
    asm volatile("csrw mie, %0" : : "r"(x));
}

#define STACK_SIZE 1024

// Saved registers for kernel context switches.
struct context {
    uint32_t ra;
    uint32_t sp;

    // callee-saved
    uint32_t s0;
    uint32_t s1;
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;
    uint32_t s8;
    uint32_t s9;
    uint32_t s10;
    uint32_t s11;
};

struct task_handler {
    uint8_t task0_stack[STACK_SIZE];
    struct context ctx_os;
    struct context ctx_task;
};
typedef struct task_handler th;
typedef struct task_handler *thP;

#endif