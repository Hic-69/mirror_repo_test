/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** parse args and split
*/

#include "../include/mysh.h"

char **parse_args(char *line)
{
    return my_str_to_array(line, ' ');
}
