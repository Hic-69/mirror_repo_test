/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** file for my env
*/

#include "../include/mysh.h"

char **copy_env(char **envp)
{
    int i = 0;
    int j = 0;
    char **copied_env = NULL;

    while (envp[i] != NULL)
        i++;
    copied_env = malloc(sizeof(char *) * (i + 1));
    while (envp[j] != NULL) {
        copied_env[j] = my_strdup(envp[j]);
        j++;
    }
    copied_env[j] = NULL;
    return copied_env;
}

void free_env(char **env)
{
    int i = 0;

    while (env[i] != NULL) {
        free(env[i]);
        i++;
    }
    free(env);
}
