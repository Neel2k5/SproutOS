#ifndef GDT_H
#define GDT_H

#include <stdint.h>

typedef struct
{
    uint16_t limit_lower;
    uint16_t base_lower;
    uint8_t base_middle;
    uint8_t access_byte;
    uint8_t limit_upperXflags;
    uint8_t base_higher;
} __attribute__((packed)) GDT_entry;

typedef struct
{
    uint16_t limit;
    uint32_t base; // ptr to gdt
} __attribute__((packed)) gdt_ptr_t;

void gdt_init(void); // to be called from kernel_main

void set_gdt_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

extern void gdt_flush(gdt_ptr_t *gdt_ptr_address); // external link to gdt.s

#endif