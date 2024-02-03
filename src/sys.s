# This Code derived from xv6-riscv (64bit)
# -- https://github.com/mit-pdos/xv6-riscv/blob/riscv/kernel/swtch.S

.globl sys_counter
.align 4
sys_counter:
	# call the C timer_handler(reg_t epc, reg_t cause)
	csrr	a0, mepc
	csrr	a1, mcause
	call	timer_oneSecondCounter

	# timer_handler will return the return address via a0.
	csrw	mepc, a0

	mret # back to interrupt location (pc=mepc)

.globl sys_timer
.align 4
sys_timer:
	# call the C timer_handler(reg_t epc, reg_t cause)
	csrr	a0, mepc
	csrr	a1, mcause
	call	timer_handler

	# timer_handler will return the return address via a0.
	csrw	mepc, a0

	mret # back to interrupt location (pc=mepc)

.globl atomic_swap
.align 4
atomic_swap:
    li a5, 1
    amoswap.w.aq a5, a5, 0(a0)
    mv a0, a5
    ret
