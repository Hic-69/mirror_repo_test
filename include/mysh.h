/*
** EPITECH PROJECT, 2026
** mysh.h
** File description:
** header of my project
*/

#ifndef MYSH_H
    #define MYSH_H

    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <string.h>
    #include <stdarg.h>
    #include <errno.h>
    #include <fcntl.h>

    #define ERR_CMD_NOT_FOUND ": Command not found.\n"
    #define SEG_FAULT "Segmentation fault\n"
    #define LEN_SEG_FAULT 19
    #define ERR_CMD_NOT_FOUND_LEN 21
    #define ERR_FORK_FAILED "fork echec :(\n"
    #define ERR_FORK_FAILED_LEN 14
    #define ERR_NO_SUCH_DIR ": No such file or directory.\n"
    #define ERR_NO_SUCH_DIR_LEN 29
    #define ERR_CD_TOO_MANY "cd: Too many arguments.\n"
    #define ERR_CD_TOO_MANY_LEN 24
    #define ERR_NULL_CMD "Invalid null command.\n"
    #define ERR_NULL_CMD_LEN 23
    #define COLOR_USER "\033[1;32m"
    #define COLOR_MYSH "\033[1;36m"
    #define COLOR_PATH "\033[1;34m"
    #define COLOR_BRANCH "\033[1;33m"
    #define COLOR_RESET "\033[0m"
    #define GIT_HEAD_PREFIX "ref: refs/heads/"
    #define MYSH_USER "god_h1c"
    #define FILE_MODE 0644

int prompt(char ***envp);
char **my_str_to_array(char *str, char sep);
char **parse_args(char *line);
char *find_path(const char *command, char **envp);
int my_strlen(const char *str);
char *my_strcat(char *dest, const char *str);
int exec_cmd(char *pathname, char **args, char **envp);
char **copy_env(char **envp);
void free_env(char **env);
int builtin_exit(char **args, int exit_code);
int builtin_env(char **my_env);
int builtin_cd(char **args, char ***env);
int builtin_setenv(char **args, char ***my_env);
int builtin_unsetenv(char **args, char **my_env);
char *my_strdup(const char *str);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(char const *s1, char const *s2, int size);
int my_strcspn(const char *str, const char *reject);
int my_getnbr(const char *str);
char *build_str(char **args);
int if_not_found(char **args, char ***my_env);
void shift_env(char **my_env, int start);
int find_home(char **my_env, char ***env);
char *search_in_dirs(char *path, const char *command);
char *build_path(const char *dir, const char *cmd);
char *drt_path(const char *command);
int handle_parent(int pid_child);
void run_child(char *pathname, char **args, char **envp);
int is_env_builtin(char ***my_env, char **args, int *exit_code);
int is_builtin(char ***my_env, char **args, int *exit_code);
int exec_line(char **args, char **envp);
void tabs_to_spaces(char *line);
void free_args(char **args);
void print_env(char **my_env);
int my_printf(const char *format, ...);
int find_old(char **my_env, char ***env);
int exec_separated(char ***envp, char *line, int *exit_code);
int exec_piped(char ***envp, char *segment, int *exit_code);
void print_prompt(char **my_env);
int apply_output_redirect(char **args, int *saved_fd);
void restore_output(int saved_fd);
void write_str(int fd, const char *str);
int get_git_branch(char *buf, int size);
#endif
