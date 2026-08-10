/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** semicolon separator handling
*/

#include "../include/mysh.h"

static void run_plain_command(char ***envp, char **args, int *exit_code)
{
    int saved_fd = -1;

    if (apply_output_redirect(args, &saved_fd) == -1) {
        *exit_code = 1;
        return;
    }
    if (!is_builtin(envp, args, exit_code))
        *exit_code = exec_line(args, *envp);
    restore_output(saved_fd);
}

static void run_segment(char ***envp, char *segment, int *exit_code)
{
    char **args = NULL;

    if (segment[0] == '\0')
        return;
    if (my_strcspn(segment, "|") != my_strlen(segment)) {
        exec_piped(envp, segment, exit_code);
        return;
    }
    args = parse_args(segment);
    if (!args || !args[0]) {
        free_args(args);
        return;
    }
    run_plain_command(envp, args, exit_code);
    free_args(args);
}

int exec_separated(char ***envp, char *line, int *exit_code)
{
    char **segments = my_str_to_array(line, ';');
    int i = 0;

    if (!segments)
        return *exit_code;
    while (segments[i] != NULL) {
        run_segment(envp, segments[i], exit_code);
        i++;
    }
    free_args(segments);
    return *exit_code;
}
