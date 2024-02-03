// reference: https://github.com/mit-pdos/xv6-riscv/blob/riscv/user/printf.c
#include <lib.h>

static char digits[] = "0123456789ABCDEF";

static void printint(int xx, int base, int sgn)
{
    char buf[16];
    int i, neg;
    uint32_t x;

    neg = 0;
    if (sgn && xx < 0) {
        neg = 1;
        x = -xx;
    } else {
        x = xx;
    }

    i = 0;
    do {
        buf[i++] = digits[x % base];
    } while ((x /= base) != 0);
    if (neg)
        buf[i++] = '-';

    while (--i >= 0)
        putc(buf[i]);
}

static void printptr(uint64_t x)
{
    int i;
    putc('0');
    putc('x');
    for (i = 0; i < (sizeof(uint64_t) * 2); i++, x <<= 4)
        putc(digits[x >> (sizeof(uint64_t) * 8 - 4)]);
}

// Print to the given fd. Only understands %d, %x, %p, %s.
void vprintf(va_list ap, const char *fmt)
{
    char *s = NULL;
    int c = 0, state = 0;

    for (int i = 0; fmt[i]; ++i) {
        c = fmt[i] & 0xFF;
        if (state == 0) {
            if (c == '%')
                state = '%';
            else
                putc(c);
        } else if (state == '%') {
            switch (c) {
            case 'd':
                printint(va_arg(ap, int), 10, 1);
                break;
            case 'l':
                printint(va_arg(ap, uint64_t), 10, 0);
                break;
            case 'x':
                printint(va_arg(ap, int), 16, 0);
                break;
            case 'p':
                printptr(va_arg(ap, uint64_t));
                break;
            case 's':
                s = va_arg(ap, char *);
                if (s == 0)
                    s = "(null)";
                while (*s != 0)
                    putc(*s++);
                break;
            case 'c':
                putc(va_arg(ap, uint32_t));
                break;
            case '%':
                putc(c);
                break;
            // Unknown % sequence.  Print it to draw attention.
            default:
                putc('%');
                putc(c);
                break;
            }
            state = 0;
        }
    }
}

void printf(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vprintf(ap, fmt);
}