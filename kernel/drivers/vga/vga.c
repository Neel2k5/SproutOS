#include "kernel/vga.h"

static size_t term_row;
static size_t term_col;
static enum vga_color term_fg;
static enum vga_color term_bg;
static uint8_t term_color;

static uint16_t *term_bfr = (uint16_t *)VGA_MEMORY;

void term_init(void)
{
    term_row = 0;
    term_col = 0;
    term_fg = VGA_COLOR_LIGHT_GREY;
    term_bg = VGA_COLOR_BLACK;
    term_color = vga_entry_color(term_fg, term_bg);

    term_clear();
}

void scroll_term(void)
{
    for (size_t y = 0; y < VGA_HEIGHT - 1; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            size_t idx1 = y * VGA_WIDTH + x;
            size_t idx2 = (y + 1) * VGA_WIDTH + x;
            term_bfr[idx1] = term_bfr[idx2];
        }
    }

    for (size_t x = 0; x < VGA_WIDTH; x++)
    {
        term_bfr[(VGA_HEIGHT - 1) * VGA_WIDTH + x] =
            vga_entry(' ', term_color);
    }

    term_row = VGA_HEIGHT - 1;
}

void term_putchar(char c)
{
    if (c == '\n')
    {
        term_col = 0;

        if (term_row == VGA_HEIGHT - 1)
            scroll_term();
        else
            term_row++;

        return;
    }

    term_bfr[term_row * VGA_WIDTH + term_col] =
        vga_entry(c, term_color);

    term_col++;

    if (term_col == VGA_WIDTH)
    {
        term_col = 0;

        if (term_row == VGA_HEIGHT - 1)
            scroll_term();
        else
            term_row++;
    }
}

void term_puts(const char *s)
{
    while (*s)
    {
        term_putchar(*s);
        s++;
    }
}
void term_puts_colored(const char *s, enum vga_color fg, enum vga_color bg)
{
    uint8_t temp = term_color;
    term_color = vga_entry_color(fg, bg);
    term_puts(s);
    term_color = temp;
}

void term_clear(void)
{
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            term_bfr[y * VGA_WIDTH + x] = vga_entry(' ', term_color);
        }
    }

    term_row = 0;
    term_col = 0;
}

void term_setcolor(enum vga_color fg, enum vga_color bg)
{
    term_bg = bg;
    term_fg = fg;
    term_color = vga_entry_color(fg, bg);
}

enum vga_color term_getfg(void)
{
    return term_fg;
}

enum vga_color term_getbg(void)
{
    return term_bg;
}