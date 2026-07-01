#include "kernel/kprintf.h"
#include "kernel/vga.h"

static void print_uint(unsigned int n)
{
    if (n == 0)
    {
        term_putchar('0');
        return;
    }
    char buf[11];
    int ptr = 0;
    while (n > 0)
    {
        buf[ptr++] = '0' + n % 10;
        n /= 10;
    }
    while (ptr--)
        term_putchar(buf[ptr]);
}
static void print_int(int n)
{
    if (n < 0)
    {
        term_putchar('-');
        print_uint((unsigned int)-n);
    }
    else
        print_uint(n);
}
static void print_hex(unsigned n)
{
    term_puts("0x");
    if (n == 0)
    {
        term_putchar('0');
        return;
    }
    char buf[8];
    int ptr = 0;
    while (n > 0)
    {
        unsigned int x = n & 0xf;
        if (x < 10)
            buf[ptr++] = x + '0';
        else
            buf[ptr++] = (x - 10) + 'A';
        n >>= 4;
    }
    while (ptr--)
        term_putchar(buf[ptr]);
}
static void ansi_setcolor(int code)
{
    switch (code)
    {
    /* Reset */
    case 0:
        term_setcolor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        break;

    /* Foreground */
    case 30:
        term_setcolor(VGA_COLOR_BLACK, term_getbg());
        break;
    case 31:
        term_setcolor(VGA_COLOR_RED, term_getbg());
        break;
    case 32:
        term_setcolor(VGA_COLOR_GREEN, term_getbg());
        break;
    case 33:
        term_setcolor(VGA_COLOR_BROWN, term_getbg());
        break;
    case 34:
        term_setcolor(VGA_COLOR_BLUE, term_getbg());
        break;
    case 35:
        term_setcolor(VGA_COLOR_MAGENTA, term_getbg());
        break;
    case 36:
        term_setcolor(VGA_COLOR_CYAN, term_getbg());
        break;
    case 37:
        term_setcolor(VGA_COLOR_LIGHT_GREY, term_getbg());
        break;

    /* Bright foreground */
    case 90:
        term_setcolor(VGA_COLOR_DARK_GREY, term_getbg());
        break;
    case 91:
        term_setcolor(VGA_COLOR_LIGHT_RED, term_getbg());
        break;
    case 92:
        term_setcolor(VGA_COLOR_LIGHT_GREEN, term_getbg());
        break;
    case 93:
        term_setcolor(VGA_COLOR_LIGHT_BROWN, term_getbg());
        break;
    case 94:
        term_setcolor(VGA_COLOR_LIGHT_BLUE, term_getbg());
        break;
    case 95:
        term_setcolor(VGA_COLOR_LIGHT_MAGENTA, term_getbg());
        break;
    case 96:
        term_setcolor(VGA_COLOR_LIGHT_CYAN, term_getbg());
        break;
    case 97:
        term_setcolor(VGA_COLOR_WHITE, term_getbg());
        break;

    /* Background */
    case 40:
        term_setcolor(term_getfg(), VGA_COLOR_BLACK);
        break;
    case 41:
        term_setcolor(term_getfg(), VGA_COLOR_RED);
        break;
    case 42:
        term_setcolor(term_getfg(), VGA_COLOR_GREEN);
        break;
    case 43:
        term_setcolor(term_getfg(), VGA_COLOR_BROWN);
        break;
    case 44:
        term_setcolor(term_getfg(), VGA_COLOR_BLUE);
        break;
    case 45:
        term_setcolor(term_getfg(), VGA_COLOR_MAGENTA);
        break;
    case 46:
        term_setcolor(term_getfg(), VGA_COLOR_CYAN);
        break;
    case 47:
        term_setcolor(term_getfg(), VGA_COLOR_LIGHT_GREY);
        break;

    /* Bright background */
    case 100:
        term_setcolor(term_getfg(), VGA_COLOR_DARK_GREY);
        break;
    case 101:
        term_setcolor(term_getfg(), VGA_COLOR_LIGHT_RED);
        break;
    case 102:
        term_setcolor(term_getfg(), VGA_COLOR_LIGHT_GREEN);
        break;
    case 103:
        term_setcolor(term_getfg(), VGA_COLOR_LIGHT_BROWN);
        break;
    case 104:
        term_setcolor(term_getfg(), VGA_COLOR_LIGHT_BLUE);
        break;
    case 105:
        term_setcolor(term_getfg(), VGA_COLOR_LIGHT_MAGENTA);
        break;
    case 106:
        term_setcolor(term_getfg(), VGA_COLOR_LIGHT_CYAN);
        break;
    case 107:
        term_setcolor(term_getfg(), VGA_COLOR_WHITE);
        break;
    }
}
static const char *parse_ansi(const char *s)
{
    if (*s++ != '\033')
        return s;
    if (*s++ != '[')
        return s;
    unsigned int code = 0;
    while (*s >= '0' && *s <= '9')
    {
        code = code * 10 + (*s - '0');
        s++;
    }
    if (*s == 'm')
    {

        ansi_setcolor(code);
        s++;
    }
    return s;
}
void kprintf(const char *s, ...)
{
    va_list args;
    va_start(args, s);

    while (*s)
    {
        if (*s == '\033')
        {
            s = parse_ansi(s);
            continue;
        }
        else if (*s != '%')
        {
            term_putchar(*s++);
            continue;
        }
        else
        {
            s++;
            switch (*s)
            {
            case 'c':
                term_putchar((char)va_arg(args, int));
                break;
            case 's':
                term_puts(va_arg(args, const char *));
                break;
            case 'u':
                print_uint(va_arg(args, unsigned int));
                break;
            case 'd':
                print_int(va_arg(args, int));
                break;
            case 'x':
                print_hex(va_arg(args, unsigned int));
                break;
            case '%':
                term_putchar('%');
                break;
            default:
                term_putchar('%');
                term_putchar(*s);
                break;
            }
            s++;
        }
    }
    va_end(args);
}