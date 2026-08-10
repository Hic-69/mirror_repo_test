/*
** EPITECH PROJECT, 2026
** my_getnbr
** File description:
** lib
*/

#include "../include/mysh.h"

int my_getnbr(char const *str)
{
    long result = 0;
    int sign = 1;
    int i = 0;

    if (!str)
        return 0;
    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-')
            sign = -sign;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (result * sign > 2147483647 ||
        result * sign < -2147483648)
        return 0;
    return result * sign;
}
