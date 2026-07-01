#include <kernel/vga.h>
#include <kernel/kprintf.h>
#include <kernel/serial.h>

void kernel_main(void)
{
    term_init();

    // Banner
    kprintf("[\033[92mSprout OS\033[0m]\n\n");

    kprintf("Log styling:\n");
    kprintf("\033[91mERR\033[0m: Error\n");
    kprintf("\033[92mOK \033[0m: Success\n");
    kprintf("\033[93mLOG\033[0m: System Log\n\n");

    kprintf("\033[93mLOG\033[0m: Initializing serial driver... ");

    if (serial_init() == 0)
    {
        kprintf("\n\033[92mOK\033[0m: Serial IO initialized\n");
        serial_puts("[Sprout OS]\n");
        serial_puts("OK: Serial IO initialized\n");
    }
    else
    {
        kprintf("\n\033[91mERR\033[0m: Serial IO init failed\n");
        serial_puts("ERR: Serial IO init failed\n");
    }
    kprintf("\033[93mLOG\033[0m: Entering idle loop...");
    serial_puts("LOG: Entering idle loop...\n");
}