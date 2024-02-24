#include "lib.h"

#define EOF 0

char *gets(char *s)
{
    int ch;
    char *p = s;

    while ((ch = getc()) != '\n' && ch != EOF) {
        if (ch == -1) {
            continue;
        }
        *s = (char) ch;
        s++;
    }

    *s = '\0';
    return p;
}

int getc(void)
{
    if (ReadUART(LSR) & LSR_RX_READY) {
        return ReadUART(RHR) == '\r' ? '\n' : ReadUART(RHR);
    } else {
        return -1;
    }
}

int putc(char ch)
{
    while ((ReadUART(LSR) & UART_LSR_EMPTY_MASK) == 0)
        ;
    return ReadUART(THR) = ch;
}

void puts(char *s)
{
    while (*s)
        putc(*s++);
}

void delay(volatile int num)
{
    num *= 50000;
    while (num--)
        ;
}