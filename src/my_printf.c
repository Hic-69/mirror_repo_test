/*
** EPITECH PROJECT, 2026
** organized
** File description:
** my_printf function
*/

#include "../include/mysh.h"

static void my_putchar(char c)
{
    write(1, &c, 1);
}

static int my_putstr(char const *str)
{
    int v = 0;

    for (v = 0; str[v] != '\0'; v++)
        write(1, &str[v], 1);
    return 0;
}

static int my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10)
        my_put_nbr(nb / 10);
    my_putchar('0' + (nb % 10));
    return nb;
}

static void type_format(char s, va_list list)
{
    if (s == '%')
        my_putchar('%');
    if (s == 'd' || s == 'i')
        my_put_nbr(va_arg(list, int));
    if (s == 'c')
        my_putchar(va_arg(list, int));
    if (s == 's')
        my_putstr(va_arg(list, char *));
}

int my_printf(const char *format, ...)
{
    va_list list;
    int i = 0;

    va_start(list, format);
    for (i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            type_format(format[i], list);
        } else {
            my_putchar(format[i]);
        }
    }
    va_end(list);
    return 0;
}
