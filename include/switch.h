#ifndef __SwITCH_H__
#define __SwITCH_H__

#include "riscv.h"

extern void sys_timer();
extern void sys_switch(struct context *ctx_old, struct context *ctx_new);

#endif
