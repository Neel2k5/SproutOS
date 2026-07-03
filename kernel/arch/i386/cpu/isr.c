#include <kernel/isr.h>
#include <kernel/kprintf.h>
#include <kernel/serial.h>

static const char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "x87 FPU Fault",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point",
    "Virtualization",
    "Control Protection",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"};

/* The C entry point called directly by assembly (isr_common_stub) */
void fault_handler(registers_t *regs)
{
    if (regs->int_no < 32)
    {
        kprintf("\n\033[91mCRIT\033[0m: !!! KERNEL PANIC !!!\n");
        serial_puts("CRIT: !!! KERNEL PANIC !!!\n");

        kprintf("\033[91mERR \033[0m: CPU Exception %d - %s\n", regs->int_no, exception_messages[regs->int_no]);
        serial_puts("ERR : CPU Exception occurred\n");

        // Register Dump
        kprintf("\033[93mDUMP\033[0m: Core Registers:\n");
        kprintf("      ERR_CODE: %x\n", regs->err_code);
        kprintf("      EIP:      %x  |  CS:  %x  |  EFLAGS: %x\n", regs->eip, regs->cs, regs->eflags);
        kprintf("      EAX:      %x  |  EBX: %x  |  ECX:    %x  |  EDX: %x\n", regs->eax, regs->ebx, regs->ecx, regs->edx);
        kprintf("      ESP:      %x  |  EBP: %x  |  ESI:    %x  |  EDI: %x\n", regs->esp, regs->ebp, regs->esi, regs->edi);
        kprintf("      DS:       %x  |  ES:  %x  |  FS:     %x  |  GS:  %x\n", regs->ds, regs->es, regs->fs, regs->gs);
        serial_puts("DUMP: Core Registers:\n");
        serial_puts("      EIP/CS/EFLAGS dumped on screen\n");
        serial_puts("      GPR arrays dumped on screen\n");

        kprintf("\033[91mHALT\033[0m: Execution frozen permanently.\n");
        serial_puts("HALT: Execution frozen permanently.\n");
        for (;;)
        {
            __asm__ __volatile__("cli; hlt");
        }
    }
}
