#include "os.h"
#include "riscv.h"

#define onesec 10000000  // cycles; about 1 second in qemu.

void timer_oneSecondClock()
{
    // each CPU has a separate source of timer interrupts.
    int id = r_mhartid();

    // ask the CLINT for a timer interrupt.
    *(uint32_t *) CLINT_MTIMECMP(id) = *(uint32_t *) CLINT_MTIME + onesec;

    // set the machine-mode trap handler.
    w_mtvec((uint32_t) sys_counter);

    // enable machine-mode interrupts.
    w_mstatus(r_mstatus() | MSTATUS_MIE);

    // enable machine-mode timer interrupts.
    w_mie(r_mie() | MIE_MTIE);
}

static int timer_count_1 = 0;

uint32_t timer_oneSecondCounter(uint32_t epc, uint32_t cause)
{
    uint32_t return_pc = epc;
    // disable machine-mode timer interrupts.
    w_mie(~((~r_mie()) | (1 << 7)));
    printf("timer_handler: %d\n", ++timer_count_1);
    int id = r_mhartid();
    *(uint32_t *) CLINT_MTIMECMP(id) = *(uint32_t *) CLINT_MTIME + onesec;
    // enable machine-mode timer interrupts.
    w_mie(r_mie() | MIE_MTIE);
    return return_pc;
}

// a scratch area per CPU for machine-mode timer interrupts.
uint32_t timer_scratch[NCPU][5];

#define interval 10000000  // cycles; about 2 second in qemu.

void timer_init()
{
    // each CPU has a separate source of timer interrupts.
    int id = r_mhartid();

    // ask the CLINT for a timer interrupt.
    *(uint32_t *) CLINT_MTIMECMP(id) = *(uint32_t *) CLINT_MTIME + interval;

    // prepare information in scratch[] for timervec.
    // scratch[0..2] : space for timervec to save registers.
    // scratch[3] : address of CLINT MTIMECMP register.
    // scratch[4] : desired interval (in cycles) between timer interrupts.
    uint32_t *scratch = &timer_scratch[id][0];
    scratch[3] = CLINT_MTIMECMP(id);
    scratch[4] = interval;
    w_mscratch((uint32_t) scratch);

    // enable machine-mode timer interrupts.
    w_mie(r_mie() | MIE_MTIE);

    printf("Timer init completed!\n");
}

static int timer_count_2 = 0;

void timer_handler()
{
    printf("timer_handler: %d\n", ++timer_count_2);
    int id = r_mhartid();
    *(uint32_t *) CLINT_MTIMECMP(id) = *(uint32_t *) CLINT_MTIME + interval;
}
