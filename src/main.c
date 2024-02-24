#include "os.h"
#include "riscv.h"

void os_init()
{
    page_init();
    user_init();
    trap_init();
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
    int num = 5;
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