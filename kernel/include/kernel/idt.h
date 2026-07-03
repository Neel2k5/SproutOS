#ifndef IDT_H
#define IDT_H
#include <stdint.h>

#define IDT_ENTRY_COUNT 256

typedef struct
{
    uint16_t offset_low;
    uint16_t segment_sel;
    uint8_t reserved;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed)) IDT_entry;
typedef struct
{
    uint16_t limit;
    uint32_t base; // ptr to idt
} __attribute__((packed)) idt_ptr_t;

#define TYPE_INTERRUPT_GATE 0x8e
#define TYPE_TRAP_GATE 0x8f
#define TYPE_TASK_GATE 0x85

void idt_init();

void set_idt_gate(int num, uint32_t offset, uint16_t segment_sel, uint8_t type_attr);

extern void idt_flush(idt_ptr_t *idt_ptr_address);

#endif