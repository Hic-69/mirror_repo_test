/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** output redirection handling
*/

#include "../include/mysh.h"

static int extract_redirect(char **args, int *out_idx, int *append)
{
    int i = 0;

    while (args[i] != NULL) {
        if (my_strcmp(args[i], ">>") == 0 && args[i + 1] != NULL) {
            *out_idx = i;
            *append = 1;
            return 1;
        }
        if (my_strcmp(args[i], ">") == 0 && args[i + 1] != NULL) {
            *out_idx = i;
            *append = 0;
            return 1;
        }
        i++;
    }
    return 0;
}

static void remove_redirect_tokens(char **args, int idx)
{
    free(args[idx]);
    free(args[idx + 1]);
    while (args[idx + 2] != NULL) {
        args[idx] = args[idx + 2];
        idx++;
    }
    args[idx] = NULL;
}

int apply_output_redirect(char **args, int *saved_fd)
{
    int idx;
    int append = 0;
    int fd;

    if (!extract_redirect(args, &idx, &append))
        return 0;
    fd = open(args[idx + 1],
        O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), FILE_MODE);
    if (fd == -1) {
        write(2, args[idx + 1], my_strlen(args[idx + 1]));
        write(2, ERR_NO_SUCH_DIR, ERR_NO_SUCH_DIR_LEN);
        remove_redirect_tokens(args, idx);
        return -1;
    }
    *saved_fd = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    remove_redirect_tokens(args, idx);
    return 1;
}

void restore_output(int saved_fd)
{
    if (saved_fd == -1)
        return;
    dup2(saved_fd, STDOUT_FILENO);
    close(saved_fd);
}
