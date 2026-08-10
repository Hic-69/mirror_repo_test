/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** tabs_to_spaces
*/

#include "../include/mysh.h"

void tabs_to_spaces(char *line)
{
    int i = 0;

    while (line[i] != '\0') {
        if (line[i] == '\t')
            line[i] = ' ';
        i++;
    }
}

void free_args(char **args)
{
    int i = 0;

    if (!args)
        return;
    while (args[i] != NULL) {
        free(args[i]);
        i++;
    }
    free(args);
}
