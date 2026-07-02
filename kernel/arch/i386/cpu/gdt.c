#include <kernel/gdt.h>

GDT_entry gdt[5];
gdt_ptr_t gdtptr;
void set_gdt_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_lower = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_higher = (base >> 24) & 0xFF;

    gdt[num].limit_lower = (limit & 0xFFFF);
    gdt[num].limit_upperXflags = (limit >> 16) & 0x0F;

    gdt[num].limit_upperXflags |= (gran & 0xF0);
    gdt[num].access_byte = access;
}
void gdt_init(void)
{
    gdtptr.limit = (sizeof(GDT_entry) * 5) - 1;
    gdtptr.base = (uint32_t)gdt;

    // gate setup
    // here 0xcf granularity sets up 4KB pages in memory

    set_gdt_gate(0, 0, 0, 0, 0); // Null Segment

    set_gdt_gate(1, 0, 0xffffffff, 0x9a, 0xcf); // Kernel Code Segment
    set_gdt_gate(2, 0, 0xffffffff, 0x92, 0xcf); // Kernel Data Segment

    set_gdt_gate(3, 0, 0xffffffff, 0xfa, 0xcf); // User Code Segment
    set_gdt_gate(4, 0, 0xffffffff, 0xf2, 0xcf); // User Data Segment

    gdt_flush(&gdtptr);
}
