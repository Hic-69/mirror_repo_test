/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** main function(entry)
*/

#include "../include/mysh.h"

int main(int ac, char **av, char **envp)
{
    int ret;
    char **my_env;

    (void)ac;
    (void)av;
    my_env = copy_env(envp);
    ret = prompt(&my_env);
    free_env(my_env);
    return ret;
}
