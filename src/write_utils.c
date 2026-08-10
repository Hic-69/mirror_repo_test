/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** generic write helpers
*/

#include "../include/mysh.h"

void write_str(int fd, const char *str)
{
    write(fd, str, my_strlen(str));
}
