#include "serial.h"

#define PORT 0x3f8 // COM1

unsigned char inb(unsigned int port) {
    unsigned char ret;
    asm volatile("inb %%dx, %%al" : "=a" (ret) : "d" (port));
    return ret;
}

void outb(unsigned int port, unsigned char value) {
    asm volatile("outb %%al, %%dx" : : "d" (port), "a" (value));
}

void serial_init() {
    // 16550 UART, which supports FIFO queues (newer than 8250)
    outb(PORT + 1, 0x00); // disable interrupts (interrupt enable register)
    outb(PORT + 3, 0x80); // enable DLAB to access certain registers(PORT+3 = line control register)
    outb(PORT + 0, 0x03); // divisor (low byte) (38400 baud) (using DLAB)
    outb(PORT + 1, 0x00); // divisor (high byte)
    outb(PORT + 3, 0x03); // turn off DLAB (bit 7), no parity (5:3), one stop bit (2), 8 bit word length (1:0)
    outb(PORT + 2, 0xc7); // writes access FIFO control register; 14 byte interrupt trigger level (7:6), clear transmit (2), receive (1) FIFO, enable FIFO (0)
    outb(PORT + 4, 0x0b); // enable auxiliary output 2 (3), request to send (1), data terminal ready (0)
}

void serial_write(char c) {
    while((inb(PORT + 5) & 0x20) == 0);
    outb(PORT, c);
}

void serial_print(char *s) {
    while(*s != '\0') {
        serial_write(*s++);
    }
}
