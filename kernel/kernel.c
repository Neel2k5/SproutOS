#include <kernel/vga.h>

void kernel_main(void)
{
    term_init();
    term_puts("[");
    term_puts_colored("Sprout OS", VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    term_puts("]\n");
    term_puts("\nLog styling\n");

    term_puts("[");
    term_puts_colored(" ERR ", VGA_COLOR_RED, VGA_COLOR_BLACK);
    term_puts("]");
    term_puts(" : Error\n");

    term_puts("[");
    term_puts_colored(" OK ", VGA_COLOR_GREEN, VGA_COLOR_BLACK);
    term_puts("]");
    term_puts(" : Success\n");

    term_puts("[");
    term_puts_colored(" WARN ", VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK);
    term_puts("]");
    term_puts(" : Warning\n");

    term_puts("\n\n[");
    term_puts_colored(" OK ", VGA_COLOR_GREEN, VGA_COLOR_BLACK);
    term_puts("]");
    term_puts(" : Entering idle loop...\n");
}