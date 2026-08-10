/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** display the prompt
*/

#include "../include/mysh.h"

int is_env_builtin(char ***my_env, char **args, int *exit_code)
{
    if (my_strcmp(args[0], "setenv") == 0) {
        *exit_code = builtin_setenv(args, my_env);
        return 1;
    }
    if (my_strcmp(args[0], "unsetenv") == 0) {
        *exit_code = builtin_unsetenv(args, *my_env);
        return 1;
    }
    return 0;
}

int is_builtin(char ***my_env, char **args, int *exit_code)
{
    if (my_strcmp(args[0], "exit") == 0) {
        builtin_exit(args, *exit_code);
        return 1;
    }
    if (my_strcmp(args[0], "env") == 0) {
        *exit_code = builtin_env(*my_env);
        return 1;
    }
    if (my_strcmp(args[0], "cd") == 0) {
        *exit_code = builtin_cd(args, my_env);
        return 1;
    }
    return is_env_builtin(my_env, args, exit_code);
}

int exec_line(char **args, char **envp)
{
    char *pathname = NULL;
    int exit_code = 0;

    pathname = find_path(args[0], envp);
    if (pathname) {
        exit_code = exec_cmd(pathname, args, envp);
    } else {
        write(2, args[0], my_strlen(args[0]));
        write(2, ERR_CMD_NOT_FOUND, ERR_CMD_NOT_FOUND_LEN);
        exit_code = 1;
    }
    return exit_code;
}

static void process_line(char ***envp, char *line, int *exit_code)
{
    tabs_to_spaces(line);
    if (line[0] == '\0')
        return;
    exec_separated(envp, line, exit_code);
}

int prompt(char ***envp)
{
    char *line = NULL;
    size_t len = 0;
    int exit_code = 0;

    while (1) {
        if (isatty(STDIN_FILENO))
            print_prompt(*envp);
        if (getline(&line, &len, stdin) == -1)
            break;
        line[my_strcspn(line, "\n")] = '\0';
        process_line(envp, line, &exit_code);
    }
    free(line);
    return exit_code;
}
