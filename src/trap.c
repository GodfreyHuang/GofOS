#include "os.h"

extern void trap_vector();

void trap_init()
{
    // set the machine-mode trap handler.
    w_mtvec((uint32_t)trap_vector);

    // enable machine-mode interrupts.
    w_mstatus(r_mstatus() | MSTATUS_MIE);
}

uint32_t trap_handler(uint32_t epc, uint32_t cause)
{
    uint32_t return_pc = epc;
    uint32_t cause_code = cause & 0xfff;

    if (cause & 0x80000000)
    {
        /* Asynchronous trap - interrupt */
        switch (cause_code)
        {
        case 3:
            puts("software interruption!\n");
            break;
        case 7:
            puts("timer interruption!\n");
            // disable machine-mode timer interrupts.
            w_mie(~((~r_mie()) | (1 << 7)));
            timer_handler();
            return_pc = (uint32_t)&os_switch;
            // enable machine-mode timer interrupts.
            w_mie(r_mie() | MIE_MTIE);
            break;
        case 11:
            puts("external interruption!\n");
            break;
        default:
            puts("unknown async exception!\n");
            break;
        }
    }
    else
    {
        /* Synchronous trap - exception */
        puts("Sync exceptions!\n");
        while (1)
        {
        /* code */
        }
    }
    return return_pc;
}