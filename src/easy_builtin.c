/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** easy_builtin cd env exit
*/

#include "../include/mysh.h"

int builtin_exit(char **args, int exit_code)
{
    if (args[1] == NULL)
        exit(exit_code);
    else
        exit(my_getnbr(args[1]));
    return 0;
}

int builtin_env(char **my_env)
{
    int i = 0;

    while (my_env[i] != NULL) {
        write(1, my_env[i], my_strlen(my_env[i]));
        write(1, "\n", 1);
        i++;
    }
    return 0;
}

static int replace_existing_env(char ***my_env, const char *key,
    const char *value, int len)
{
    int i = 0;

    while ((*my_env)[i] != NULL) {
        if (my_strncmp((*my_env)[i], key, len) == 0
            && (*my_env)[i][len] == '=') {
            free((*my_env)[i]);
            (*my_env)[i] = malloc(len + 1 + my_strlen(value) + 1);
            (*my_env)[i][0] = '\0';
            my_strcat((*my_env)[i], key);
            my_strcat((*my_env)[i], "=");
            my_strcat((*my_env)[i], value);
            return 1;
        }
        i++;
    }
    return 0;
}

static void update_env(char ***my_env, const char *key, const char *value)
{
    char *args[3];

    if (replace_existing_env(my_env, key, value, my_strlen(key)))
        return;
    args[0] = NULL;
    args[1] = (char *)key;
    args[2] = (char *)value;
    if_not_found(args, my_env);
}

static int do_chdir(const char *path, char ***my_env)
{
    char old_pwd[4096];
    char new_pwd[4096];

    getcwd(old_pwd, sizeof(old_pwd));
    if (chdir(path) == -1)
        return -1;
    getcwd(new_pwd, sizeof(new_pwd));
    update_env(my_env, "OLDPWD", old_pwd);
    update_env(my_env, "PWD", new_pwd);
    return 0;
}

int find_home(char **my_env, char ***env)
{
    int i;

    for (i = 0; my_env[i] != NULL; i++) {
        if (my_strncmp(my_env[i], "HOME=", 5) == 0)
            return do_chdir(my_env[i] + 5, env);
    }
    return 0;
}

int find_old(char **my_env, char ***env)
{
    int i;
    char *old_path;

    for (i = 0; my_env[i] != NULL; i++) {
        if (my_strncmp(my_env[i], "OLDPWD=", 7) == 0) {
            old_path = my_env[i] + 7;
            return do_chdir(old_path, env);
        }
    }
    write(2, ERR_NO_SUCH_DIR, ERR_NO_SUCH_DIR_LEN);
    return 1;
}

static void print_chdir_error(const char *path)
{
    write(2, path, my_strlen(path));
    write(2, ": ", 2);
    write(2, strerror(errno), my_strlen(strerror(errno)));
    write(2, ".\n", 2);
}

int builtin_cd(char **args, char ***my_env)
{
    if (args[1] != NULL && args[2] != NULL) {
        write(2, ERR_CD_TOO_MANY, ERR_CD_TOO_MANY_LEN);
        return 1;
    }
    if (args[1] == NULL || my_strcmp(args[1], "~") == 0
        || my_strcmp(args[1], "--") == 0)
        return find_home(*my_env, my_env);
    if (my_strcmp(args[1], "-") == 0)
        return find_old(*my_env, my_env);
    if (do_chdir(args[1], my_env) == -1) {
        print_chdir_error(args[1]);
        return 1;
    }
    return 0;
}
