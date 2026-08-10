/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** setenv builtin
*/

#include "../include/mysh.h"

static int is_valid_char(char c)
{
    return (c == '_') || (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

static int check_name(char *name)
{
    int i = 1;

    if (!((name[0] == '_') || (name[0] >= 'a' && name[0] <= 'z') ||
            (name[0] >= 'A' && name[0] <= 'Z'))) {
        my_printf("setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    while (name[i] != '\0') {
        if (!is_valid_char(name[i])) {
            my_printf("setenv: Variable name must contain ");
            my_printf("alphanumeric characters.\n");
            return 1;
        }
        i++;
    }
    return 0;
}

static int too_many_args(char **args)
{
    if (args[2] != NULL && args[3] != NULL) {
        my_printf("setenv: Too many arguments.\n");
        return 1;
    }
    return 0;
}

static int replace_or_add(char **args, char ***my_env)
{
    int i = 0;
    int len = my_strlen(args[1]);

    while ((*my_env)[i] != NULL) {
        if (my_strncmp((*my_env)[i], args[1], len) == 0
            && (*my_env)[i][len] == '=') {
            free((*my_env)[i]);
            (*my_env)[i] = build_str(args);
            return 0;
        }
        i++;
    }
    return if_not_found(args, my_env);
}

int builtin_setenv(char **args, char ***my_env)
{
    if (!args[1]) {
        print_env(*my_env);
        return 0;
    }
    if (too_many_args(args) || check_name(args[1]))
        return 1;
    return replace_or_add(args, my_env);
}
