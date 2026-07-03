#include <kernel/idt.h>
#include <kernel/isr.h>

IDT_entry idt[IDT_ENTRY_COUNT];
idt_ptr_t idt_ptr;

void set_idt_gate(int num, uint32_t offset, uint16_t segment_sel, uint8_t type_attr)
{
    idt[num].offset_low = (offset & 0xFFFF);
    idt[num].segment_sel = segment_sel;
    idt[num].reserved = 0;
    idt[num].type_attr = type_attr;
    idt[num].offset_high = (offset >> 16) & 0xFFFF;
}

void idt_init()
{
    idt_ptr.limit = (sizeof(IDT_entry) * IDT_ENTRY_COUNT) - 1;
    idt_ptr.base = (uint32_t)&idt;

    for (int i = 0; i < IDT_ENTRY_COUNT; i++)
    {
        set_idt_gate(i, 0, 0, 0);
    }

    // 32 core CPU interrupts for kernel (0x08 is kernel code segment)
    set_idt_gate(0, (uint32_t)_isr0, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(1, (uint32_t)_isr1, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(2, (uint32_t)_isr2, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(3, (uint32_t)_isr3, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(4, (uint32_t)_isr4, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(5, (uint32_t)_isr5, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(6, (uint32_t)_isr6, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(7, (uint32_t)_isr7, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(8, (uint32_t)_isr8, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(9, (uint32_t)_isr9, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(10, (uint32_t)_isr10, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(11, (uint32_t)_isr11, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(12, (uint32_t)_isr12, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(13, (uint32_t)_isr13, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(14, (uint32_t)_isr14, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(15, (uint32_t)_isr15, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(16, (uint32_t)_isr16, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(17, (uint32_t)_isr17, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(18, (uint32_t)_isr18, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(19, (uint32_t)_isr19, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(20, (uint32_t)_isr20, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(21, (uint32_t)_isr21, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(22, (uint32_t)_isr22, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(23, (uint32_t)_isr23, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(24, (uint32_t)_isr24, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(25, (uint32_t)_isr25, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(26, (uint32_t)_isr26, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(27, (uint32_t)_isr27, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(28, (uint32_t)_isr28, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(29, (uint32_t)_isr29, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(30, (uint32_t)_isr30, 0x08, TYPE_INTERRUPT_GATE);
    set_idt_gate(31, (uint32_t)_isr31, 0x08, TYPE_INTERRUPT_GATE);

    idt_flush(&idt_ptr);
}
