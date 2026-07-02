#include <kernel/vga.h>
#include <kernel/kprintf.h>
#include <kernel/serial.h>
#include <kernel/gdt.h>

void kernel_main(void)
{
    gdt_init();
    term_init();

    kprintf("[\033[92mSprout OS\033[0m]\n\n");

    kprintf("\033[93mLOG\033[0m: Dumping pre VGA initialisation logs\n");

    kprintf("\033[92mOK \033[0m: Kernel Loaded\n");
    kprintf("\033[92mOK \033[0m: GDT initialized\n");
    kprintf("\033[92mOK \033[0m: VGA initialized\n");
    kprintf("\033[93mLOG\033[0m: Initializing serial driver...\n");

    if (serial_init() == 0)
    {
        kprintf("\033[92mOK \033[0m: Serial IO initialized\n");

        // Mirror previous logs to serial
        serial_puts("[Sprout OS]\n\n");

        serial_puts("LOG : Dumping pre VGA initialisation logs\n");
        serial_puts("OK : Kernel Loaded\n");
        serial_puts("OK : GDT initialized\n");
        serial_puts("OK : VGA initialized\n");

        serial_puts("LOG : Dumping pre Serial IO initialisation logs\n");
        serial_puts("LOG: Initializing serial driver...\n");
        serial_puts("OK : Serial IO initialized\n");

        kprintf("\033[93mLOG\033[0m: Mirrored boot log to Serial Port\n");
        serial_puts("LOG: Mirrored boot log to Serial Port\n");
    }
    else
    {
        kprintf("\033[91mERR\033[0m: Serial IO init failed\n");
    }

    kprintf("\033[93mLOG\033[0m: Kernel initialization complete\n");
    kprintf("\033[93mLOG\033[0m: Entering idle loop...\n");

    serial_puts("LOG: Kernel initialization complete\n");
    serial_puts("LOG: Entering idle loop...\n");
}