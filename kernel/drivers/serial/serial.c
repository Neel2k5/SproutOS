#include <kernel/serial.h>

int serial_init(void)
{
    outb(COM1 + 1, 0x00); // Disable interrupts
    outb(COM1 + 3, 0x80); // Enable DLAB
    outb(COM1 + 0, 0x03); // Baud divisor low (38400 baud)
    outb(COM1 + 1, 0x00); // Baud divisor high
    outb(COM1 + 3, 0x03); // 8 bits, no parity, 1 stop bit
    outb(COM1 + 2, 0xC7); // Enable FIFO
    outb(COM1 + 4, 0x0B); // IRQs enabled, RTS/DSR set

    // Loopback test
    outb(COM1 + 4, 0x1E);
    outb(COM1 + 0, 0xAE);

    if (inb(COM1 + 0) != 0xAE)
        return 1;

    // Normal operation
    outb(COM1 + 4, 0x0F);

    return 0;
}

int serial_received(void)
{
    return inb(COM1 + 5) & 1;
}

char serial_read(void)
{
    while (!serial_received())
        ;

    return inb(COM1);
}

int serial_transmit_empty(void)
{
    return inb(COM1 + 5) & 0x20;
}

void serial_putchar(char c)
{
    while (!serial_transmit_empty())
        ;

    outb(COM1, c);
}

void serial_puts(const char *str)
{
    while (*str)
        serial_putchar(*str++);
}