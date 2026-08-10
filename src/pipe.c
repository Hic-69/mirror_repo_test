/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** pipe handling
*/

#include "../include/mysh.h"

static int count_cmds(char **cmds)
{
    int n = 0;

    while (cmds[n] != NULL)
        n++;
    return n;
}

static void run_child_stage(char ***envp, char *cmd_str, int in_fd, int out_fd)
{
    char **args = parse_args(cmd_str);
    int exit_code = 0;

    if (in_fd != STDIN_FILENO)
        dup2(in_fd, STDIN_FILENO);
    if (out_fd != STDOUT_FILENO)
        dup2(out_fd, STDOUT_FILENO);
    if (!args || !args[0])
        exit(0);
    if (is_builtin(envp, args, &exit_code))
        exit(exit_code);
    exit(exec_line(args, *envp));
}

static int spawn_stage(char ***envp, char *cmd_str, int in_fd, int out_fd)
{
    int pid = fork();

    if (pid == 0)
        run_child_stage(envp, cmd_str, in_fd, out_fd);
    if (pid < 0)
        write(2, ERR_FORK_FAILED, ERR_FORK_FAILED_LEN);
    return pid;
}

static int wait_all(int *pids, int n)
{
    int status = 0;
    int i = 0;

    while (i < n) {
        waitpid(pids[i], &status, 0);
        i++;
    }
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

static int handle_null_pipe_char(char c, int *has_word)
{
    if (c == '|' && !*has_word)
        return 1;
    if (c == '|')
        *has_word = 0;
    else if (c != ' ')
        *has_word = 1;
    return 0;
}

static int is_null_pipe(char *segment)
{
    int i = 0;
    int has_word = 0;

    while (segment[i] != '\0') {
        if (handle_null_pipe_char(segment[i], &has_word))
            return 1;
        i++;
    }
    return !has_word;
}

static int spawn_and_link(char ***envp, char **cmds, int i, int *in_fd)
{
    int fds[2];
    int pid;

    if (cmds[i + 1] != NULL)
        pipe(fds);
    pid = spawn_stage(envp, cmds[i], *in_fd,
        cmds[i + 1] ? fds[1] : STDOUT_FILENO);
    if (cmds[i + 1] != NULL)
        close(fds[1]);
    if (*in_fd != STDIN_FILENO)
        close(*in_fd);
    *in_fd = cmds[i + 1] ? fds[0] : *in_fd;
    return pid;
}

static int run_pipeline(char ***envp, char **cmds, int n)
{
    int *pids = malloc(sizeof(int) * n);
    int in_fd = STDIN_FILENO;
    int i = 0;
    int code;

    while (cmds[i] != NULL) {
        pids[i] = spawn_and_link(envp, cmds, i, &in_fd);
        i++;
    }
    code = wait_all(pids, n);
    free(pids);
    return code;
}

int exec_piped(char ***envp, char *segment, int *exit_code)
{
    char **cmds;
    int n;

    if (is_null_pipe(segment)) {
        write(2, ERR_NULL_CMD, ERR_NULL_CMD_LEN);
        *exit_code = 1;
        return 1;
    }
    cmds = my_str_to_array(segment, '|');
    n = count_cmds(cmds);
    *exit_code = run_pipeline(envp, cmds, n);
    free_args(cmds);
    return *exit_code;
}
