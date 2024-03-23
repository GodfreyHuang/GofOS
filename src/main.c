#include "os.h"
#include "riscv.h"
#include "uart.h"

#define LSR_RX_READY (1 << 0)
#define EOF 0

void uart_init()
{
    /* disable interrupts */
    WriteUART(ReadUART(IER), 0x00);

    /* Baud rate setting */
    uint8_t lcr = ReadUART(LCR);
    WriteUART(ReadUART(LCR), lcr | (1 << 7));
    WriteUART(ReadUART(UART0 + 0x00), 0x03);
    WriteUART(ReadUART(UART0 + 0x01), 0x00);

    lcr = 0;
    WriteUART(ReadUART(LCR), lcr | (3 << 0));

    uint8_t ier = ReadUART(IER);
    WriteUART(ReadUART(IER), ier | (1 << 0));
}

void os_init()
{
    uart_init();
    page_init();
    user_init();
    trap_init();
    plic_init();
    timer_init();
    puts("GofOS boot completed!\n\n");
}

int main(int argc, char *argv[])
{
    // init os setting
    os_init();

    // printf test
    printf("The message of printf, print number %d\n", 100);

    // malloc test
    page_test();
    printf("\n\n");

    // multitasking test
    int current_task = 0;
    int num = 10;
    while (num--) {
        puts("OS: Activate next task\n");
        task_switchTask(current_task);
        puts("OS: Back to OS\n");
        current_task = (current_task + 1) % taskTop;  // Round Robin Scheduling
        puts("\n");
        printf("num = %d\n", num);
    }

    printf("End Multitasking Test.\n");

    // timer_oneSecondClock(); // start timer interrupt ...
    while (1) {
    }

    return 0;
}