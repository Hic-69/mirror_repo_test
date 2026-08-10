/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** colored prompt rendering
*/

#include "../include/mysh.h"

static void print_branch(void)
{
    char branch[128];

    if (!get_git_branch(branch, sizeof(branch)))
        return;
    write_str(1, COLOR_BRANCH "(");
    write_str(1, branch);
    write_str(1, ")" COLOR_RESET);
}

void print_prompt(char **my_env)
{
    char cwd[4096];

    (void)my_env;
    getcwd(cwd, sizeof(cwd));
    write_str(1, "{" COLOR_USER MYSH_USER COLOR_RESET "@" COLOR_MYSH "mysh");
    write_str(1, COLOR_RESET "}->{");
    write_str(1, COLOR_PATH);
    write_str(1, cwd);
    write_str(1, COLOR_RESET "}");
    print_branch();
    write_str(1, "$> ");
}
