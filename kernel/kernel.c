#include <kernel/vga.h>
#include <kernel/kprintf.h>

void kernel_main(void)
{
    term_init();

    kprintf(
        "[\033[92mSprout OS\033[0m]\n\n"
        "Log styling\n"

        "\033[91mERR\033[0m: Error\n"
        "\033[92mOK\033[0m: Success\n"
        "\033[93mLOG \033[0m: System Log\n\n"

        "\033[93mLOG\033[0m: Entering idle loop...\n");
}