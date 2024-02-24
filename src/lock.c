#include "os.h"

void basic_lock()
{
    w_mstatus(r_mstatus() & ~MSTATUS_MIE);
}

void basic_unlock()
{
    w_mstatus(r_mstatus() | MSTATUS_MIE);
}

void lock_init(lock_t *l)
{
    l->locked = 0;
}

void lock_free(lock_t *l)
{
    l->locked = 0;
}

void lock_acquire(lock_t *l)
{
    for(;;)
    {
        if(!atomic_swap(l))
            break;
    }
}