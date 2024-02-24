// Reference: https://github.com/mit-pdos/xv6-riscv/blob/riscv/kernel/memlayout.h 
// QEMU UART Setting
#define UART0 0x10000000L

#define Reg(reg) ((volatile unsigned char *) (UART0 + reg))

#define RHR 0  // receive holding register (for input bytes)
#define THR 0  // transmit holding register (for output bytes)
#define IER 1  // interrupt enable register
#define IER_RX_ENABLE (1 << 0)
#define IER_TX_ENABLE (1 << 1)
#define FCR 2  // FIFO control register
#define FCR_FIFO_ENABLE (1 << 0)
#define FCR_FIFO_CLEAR (3 << 1)  // clear the content of the two FIFOs
#define ISR 2                    // interrupt status register
#define LCR 3                    // line control register
#define LCR_EIGHT_BITS (3 << 0)
#define LCR_BAUD_LATCH (1 << 7)  // special mode to set baud rate
#define LSR 5                    // line status register
#define LSR_RX_READY (1 << 0)    // input is waiting to be read from RHR
#define LSR_TX_IDLE (1 << 5)     // THR can accept another character to send

#define UART_LSR_RX_READY 0x01  // input is waiting to be read from RHR
#define UART_LSR_EMPTY_MASK \
    0x40  // LSR Bit 6: When LSR Bit 6 is 1, which means Transmitter is empty
          // (Transmitter empty; both the THR and LSR are empty)

#define ReadUART(reg) (*(Reg(reg)))
#define WriteUART(reg, v) (*(Reg(reg)) = (v))

#define UART0_IRQ 10
#define VIRTIO_IRQ 1