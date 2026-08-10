/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** unsetenv builtin
*/

#include "../include/mysh.h"

static int remove_one(char *name, char **my_env)
{
    int i = 0;
    int len = my_strlen(name);

    while (my_env[i] != NULL) {
        if (my_strncmp(my_env[i], name, len) == 0
            && my_env[i][len] == '=') {
            free(my_env[i]);
            shift_env(my_env, i);
            return 0;
        }
        i++;
    }
    return 0;
}

int builtin_unsetenv(char **args, char **my_env)
{
    int i = 1;

    if (!args[1]) {
        my_printf("unsetenv: Too few arguments.\n");
        return 1;
    }
    while (args[i] != NULL) {
        remove_one(args[i], my_env);
        i++;
    }
    return 0;
}
