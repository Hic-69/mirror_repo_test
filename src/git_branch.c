/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** git branch detection for the prompt
*/

#include "../include/mysh.h"

int get_git_branch(char *buf, int size)
{
    int fd = open(".git/HEAD", O_RDONLY);
    int len;
    int i = 0;
    int prefix_len = my_strlen(GIT_HEAD_PREFIX);

    if (fd == -1)
        return 0;
    len = read(fd, buf, size - 1);
    close(fd);
    if (len <= prefix_len || my_strncmp(buf, GIT_HEAD_PREFIX, prefix_len) != 0)
        return 0;
    while (i + prefix_len < len && buf[i + prefix_len] != '\n') {
        buf[i] = buf[i + prefix_len];
        i++;
    }
    buf[i] = '\0';
    return 1;
}
