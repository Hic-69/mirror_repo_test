/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** execute the command
*/

#include "../include/mysh.h"

void run_child(char *pathname, char **args, char **envp)
{
    execve(pathname, args, envp);
    write_str(2, pathname);
    write_str(2, ": ");
    write_str(2, strerror(errno));
    if (errno == ENOEXEC)
        write_str(2, ". Wrong Architecture");
    write_str(2, ".\n");
    exit(1);
}

int handle_parent(int pid_child)
{
    int status;

    waitpid(pid_child, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)
        write(2, SEG_FAULT, LEN_SEG_FAULT);
    return 0;
}

int exec_cmd(char *pathname, char **args, char **envp)
{
    int pid_child;

    pid_child = fork();
    if (pid_child == 0)
        run_child(pathname, args, envp);
    if (pid_child > 0)
        return handle_parent(pid_child);
    write(2, ERR_FORK_FAILED, ERR_FORK_FAILED_LEN);
    return 1;
}
