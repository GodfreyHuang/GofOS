#include "os.h"

lock_t lock;
static int var = 1000;

void os_switch()
{
    task_switchOS();
}

void os_task0(void)
{
    puts("Task0: Created!\n");
    puts("Task0 return to kernel mode\n");
    os_switch();
    while (1) {
        puts("Task0: Running...\n");
        delay(1000);
        os_switch();
    }
}

void os_task1(void)
{
    puts("Task1: Created!\n");
    puts("Task1 return to kernel mode\n");
    os_switch();
    while (1) {
        puts("Task1: Running...\n");
        delay(1000);
        os_switch();
    }
}

void os_task2(void)
{
    puts("Task2: Created!\n");
    while (1) {
        puts("Execute Task2...\n");
        delay(1000);
    }
}

void os_task3(void)
{
    puts("Task3: Created!\n");
    while (1) {
        puts("Execute Task3...\n");
        delay(1000);
    }
}

void os_task4(void)
{
    puts("Task4: Created!\n");
    while (1) {
        for(int i = 0; i < 50; ++i)
        {
            lock_acquire(&lock);
            var += 5;
            lock_free(&lock);
            delay(100);
        }
        printf("The value of shared_var is: %d\n", var);
    }
}

void user_init()
{
    lock_init(&lock);
    task_create(&os_task0);
    task_create(&os_task1);
    task_create(&os_task2);
    task_create(&os_task3);
    task_create(&os_task4);
    printf("User init completed!\n");
}
