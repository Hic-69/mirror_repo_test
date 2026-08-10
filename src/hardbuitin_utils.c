/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** hard_builtin utils
*/

#include "../include/mysh.h"

void shift_env(char **my_env, int start)
{
    int i = start;

    while (my_env[i + 1] != NULL) {
        my_env[i] = my_env[i + 1];
        i++;
    }
    my_env[i] = NULL;
}

char *build_str(char **args)
{
    char *new_str;
    int len2 = args[2] ? my_strlen(args[2]) : 0;

    new_str = malloc(my_strlen(args[1]) + 1 + len2 + 1);
    new_str[0] = '\0';
    my_strcat(new_str, args[1]);
    my_strcat(new_str, "=");
    if (args[2])
        my_strcat(new_str, args[2]);
    return new_str;
}

int if_not_found(char **args, char ***my_env)
{
    char **new_env = NULL;
    int n = 0;
    int i = 0;

    while ((*my_env)[n] != NULL)
        n++;
    new_env = malloc(sizeof(char *) * (n + 2));
    for (i = 0; i < n; i++)
        new_env[i] = ((*my_env)[i]);
    new_env[n] = build_str(args);
    new_env[n + 1] = NULL;
    free(*my_env);
    *my_env = new_env;
    return 0;
}

void print_env(char **my_env)
{
    int i = 0;

    while (my_env[i] != NULL) {
        my_printf("%s", my_env[i]);
        my_printf("\n");
        i++;
    }
}
