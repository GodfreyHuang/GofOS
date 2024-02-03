# This Code derived from xv6-riscv (64bit)
# -- https://github.com/mit-pdos/xv6-riscv/blob/riscv/kernel/swtch.S

# Context switch
#
#   void sys_switch(struct context *old, struct context *new);
# 
# Save current registers in old. Load from new.

# ============ MACRO ==================
.macro ctx_save base
        sw ra, 0(\base)
        sw sp, 4(\base)
        sw s0, 8(\base)
        sw s1, 12(\base)
        sw s2, 16(\base)
        sw s3, 20(\base)
        sw s4, 24(\base)
        sw s5, 28(\base)
        sw s6, 32(\base)
        sw s7, 36(\base)
        sw s8, 40(\base)
        sw s9, 44(\base)
        sw s10, 48(\base)
        sw s11, 52(\base)
.endm

.macro ctx_load base
        lw ra, 0(\base)
        lw sp, 4(\base)
        lw s0, 8(\base)
        lw s1, 12(\base)
        lw s2, 16(\base)
        lw s3, 20(\base)
        lw s4, 24(\base)
        lw s5, 28(\base)
        lw s6, 32(\base)
        lw s7, 36(\base)
        lw s8, 40(\base)
        lw s9, 44(\base)
        lw s10, 48(\base)
        lw s11, 52(\base)
.endm

# ============ Macro END   ==================

.globl sys_switch
.align 4
sys_switch:
        ctx_save a0  # a0 => struct context *old
        ctx_load a1  # a1 => struct context *new
        ret          # pc=ra; swtch to new task (new->ra)

.globl trap_vector
# trap vector 的記憶體地址必須以 4-byte 進行對齊
.align 4
trap_vector:
        # 儲存 context (暫存器)
        csrrw   t6, mscratch, t6
        ctx_save t6
        csrw    mscratch, t6
        # 呼叫 trap.c 的 trap 處理程式
        csrr    a0, mepc
        csrr    a1, mcause
        call    trap_handler

        # trap 處理程式會回傳 a0 的記憶體位置
        csrw    mepc, a0

        #處理完成後將 context 載回
        csrr    t6, mscratch
        ctx_load  t6
        mret
