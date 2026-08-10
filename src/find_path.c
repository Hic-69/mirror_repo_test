/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** create the path
*/

#include "../include/mysh.h"

char *drt_path(const char *command)
{
    if (access(command, F_OK) == 0)
        return my_strdup(command);
    return NULL;
}

char *build_path(const char *dir, const char *cmd)
{
    int len_total;
    char *full_path = NULL;

    len_total = my_strlen(dir) + 1 + my_strlen(cmd) + 1;
    full_path = malloc(sizeof(char) * len_total);
    if (!full_path)
        return NULL;
    full_path[0] = '\0';
    my_strcat(full_path, dir);
    my_strcat(full_path, "/");
    my_strcat(full_path, cmd);
    return full_path;
}

char *search_in_dirs(char *path, const char *command)
{
    int j = 0;
    char **stock_path;
    char *pathname;

    stock_path = my_str_to_array(path, ':');
    while (stock_path[j] != NULL) {
        pathname = build_path(stock_path[j], command);
        if (access(pathname, X_OK) == 0)
            return pathname;
        free(pathname);
        j++;
    }
    return NULL;
}

char *find_path(const char *command, char **envp)
{
    int i;
    char *path;

    for (i = 0; command[i] != '\0'; i++) {
        if (command[i] == '/')
            return drt_path(command);
    }
    i = 0;
    while (envp[i] != NULL) {
        if (my_strncmp(envp[i], "PATH=", 5) == 0) {
            path = envp[i] + 5;
            return search_in_dirs(path, command);
        }
        i++;
    }
    return NULL;
}
