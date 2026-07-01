#ifndef KERNEL_SERIAL_H
#define KERNEL_SERIAL_H

#include <stdint.h>
#include <kernel/io.h>

#define COM1 0x3F8

int serial_init(void);

int serial_received(void);
char serial_read(void);

int serial_transmit_empty(void);
void serial_putchar(char c);
void serial_puts(const char *str);

#endif /* KERNEL_SERIAL_H */