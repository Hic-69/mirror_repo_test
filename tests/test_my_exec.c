/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** unit tests
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mysh.h"

Test(my_strlen, basic_string)
{
    cr_assert_eq(my_strlen("hello"), 5);
}

Test(my_strlen, empty_string)
{
    cr_assert_eq(my_strlen(""), 0);
}

Test(my_strlen, string_with_spaces)
{
    cr_assert_eq(my_strlen("ls -la"), 6);
}

Test(my_strlen, single_char)
{
    cr_assert_eq(my_strlen("a"), 1);
}

Test(my_strcat, basic_concat)
{
    char dest[20] = "hello";

    my_strcat(dest, " world");
    cr_assert_str_eq(dest, "hello world");
}

Test(my_strcat, concat_empty_src)
{
    char dest[20] = "hello";

    my_strcat(dest, "");
    cr_assert_str_eq(dest, "hello");
}

Test(my_strcat, returns_dest)
{
    char dest[20] = "foo";
    char *ret = my_strcat(dest, "bar");

    cr_assert_eq(ret, dest);
}

Test(my_strcat, concat_to_empty_dest)
{
    char dest[20] = "";

    my_strcat(dest, "hello");
    cr_assert_str_eq(dest, "hello");
}

Test(my_str_to_array, split_by_space)
{
    char **arr = my_str_to_array("ls -la .", ' ');

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "ls");
    cr_assert_str_eq(arr[1], "-la");
    cr_assert_str_eq(arr[2], ".");
    cr_assert_null(arr[3]);
}

Test(my_str_to_array, split_by_colon)
{
    char **arr = my_str_to_array("/usr/bin:/bin:/usr/sbin", ':');

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "/usr/bin");
    cr_assert_str_eq(arr[1], "/bin");
    cr_assert_str_eq(arr[2], "/usr/sbin");
    cr_assert_null(arr[3]);
}

Test(my_str_to_array, last_element_is_null)
{
    char **arr = my_str_to_array("one two", ' ');

    cr_assert_null(arr[2]);
}

Test(my_str_to_array, multiple_consecutive_separators)
{
    char **arr = my_str_to_array("ls  -la", ' ');

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "ls");
    cr_assert_str_eq(arr[1], "-la");
    cr_assert_null(arr[2]);
}

Test(my_str_to_array, single_word)
{
    char **arr = my_str_to_array("ls", ' ');

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "ls");
    cr_assert_null(arr[1]);
}

Test(parse_args, command_with_args)
{
    char **arr = parse_args("echo hello world");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "echo");
    cr_assert_str_eq(arr[1], "hello");
    cr_assert_str_eq(arr[2], "world");
    cr_assert_null(arr[3]);
}

Test(parse_args, command_only)
{
    char **arr = parse_args("ls");

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "ls");
    cr_assert_null(arr[1]);
}

Test(find_path, finds_existing_command)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char *result = find_path("ls", env);

    cr_assert_not_null(result);
    free(result);
}

Test(find_path, returns_null_for_unknown_command)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char *result = find_path("commandquiexistepas42", env);

    cr_assert_null(result);
}

Test(find_path, returns_null_without_path_in_env)
{
    char *env[] = {"HOME=/home/user", "USER=hic", NULL};
    char *result = find_path("ls", env);

    cr_assert_null(result);
}

Test(find_path, finds_echo)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char *result = find_path("echo", env);

    cr_assert_not_null(result);
    free(result);
}

Test(find_path, absolute_path_existing)
{
    char *env[] = {NULL};
    char *result = find_path("/bin/ls", env);

    cr_assert_not_null(result);
    free(result);
}

Test(find_path, absolute_path_not_existing)
{
    char *env[] = {NULL};
    char *result = find_path("/bin/commandquiexistepas", env);

    cr_assert_null(result);
}

Test(exec_cmd, returns_zero_on_success)
{
    char *args[] = {"/bin/true", NULL};
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    int ret = exec_cmd("/bin/true", args, env);

    cr_assert_eq(ret, 0);
}

Test(exec_cmd, returns_nonzero_on_failure)
{
    char *args[] = {"/bin/false", NULL};
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    int ret = exec_cmd("/bin/false", args, env);

    cr_assert_neq(ret, 0);
}

Test(exec_cmd, returns_correct_exit_code)
{
    char *args[] = {"/bin/sh", "-c", "exit 42", NULL};
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    int ret = exec_cmd("/bin/sh", args, env);

    cr_assert_eq(ret, 42);
}

Test(exec_cmd, runs_ls)
{
    char *args[] = {"/bin/ls", "/tmp", NULL};
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    int ret = exec_cmd("/bin/ls", args, env);

    cr_assert_eq(ret, 0);
}

Test(copy_env, returns_not_null)
{
    char *env[] = {"PATH=/usr/bin", "HOME=/home/hic", NULL};
    char **copy = copy_env(env);

    cr_assert_not_null(copy);
    free_env(copy);
}

Test(copy_env, values_are_equal)
{
    char *env[] = {"PATH=/usr/bin", "HOME=/home/hic", NULL};
    char **copy = copy_env(env);

    cr_assert_str_eq(copy[0], "PATH=/usr/bin");
    cr_assert_str_eq(copy[1], "HOME=/home/hic");
    cr_assert_null(copy[2]);
    free_env(copy);
}

Test(copy_env, pointers_are_different)
{
    char *env[] = {"PATH=/usr/bin", "HOME=/home/hic", NULL};
    char **copy = copy_env(env);

    cr_assert_neq(copy[0], env[0]);
    cr_assert_neq(copy[1], env[1]);
    free_env(copy);
}

Test(copy_env, empty_env)
{
    char *env[] = {NULL};
    char **copy = copy_env(env);

    cr_assert_not_null(copy);
    cr_assert_null(copy[0]);
    free_env(copy);
}

Test(builtin_exit, exits_with_zero, .exit_code = 0)
{
    char *args[] = {"exit", NULL};

    builtin_exit(args, 0);
}

Test(builtin_exit, exits_with_42, .exit_code = 42)
{
    char *args[] = {"exit", "42", NULL};

    builtin_exit(args, 0);
}

Test(builtin_exit, exits_with_1, .exit_code = 1)
{
    char *args[] = {"exit", "1", NULL};

    builtin_exit(args, 0);
}

Test(builtin_cd, changes_to_tmp)
{
    char *env[] = {"HOME=/home/hic", NULL};
    char **my_env = copy_env(env);
    char *args[] = {"cd", "/tmp", NULL};
    char cwd[256];

    builtin_cd(args, &my_env);
    getcwd(cwd, 256);
    cr_assert_str_eq(cwd, "/tmp");
    free_env(my_env);
}

Test(builtin_cd, returns_error_on_invalid_path)
{
    char *env[] = {"HOME=/home/hic", NULL};
    char **my_env = copy_env(env);
    char *args[] = {"cd", "/dossierquiexistepas42", NULL};
    int ret = builtin_cd(args, &my_env);

    cr_assert_eq(ret, 1);
    free_env(my_env);
}

Test(builtin_cd, goes_home_without_argument)
{
    char *env[] = {"HOME=/tmp", NULL};
    char **my_env = copy_env(env);
    char *args[] = {"cd", NULL};
    char cwd[256];

    builtin_cd(args, &my_env);
    getcwd(cwd, 256);
    cr_assert_str_eq(cwd, "/tmp");
    free_env(my_env);
}

Test(builtin_cd, too_many_arguments_returns_one)
{
    char *env[] = {"HOME=/home/hic", NULL};
    char **my_env = copy_env(env);
    char *args[] = {"cd", "/tmp", "/home", NULL};
    int ret = builtin_cd(args, &my_env);

    cr_assert_eq(ret, 1);
    free_env(my_env);
}

Test(builtin_cd, dash_goes_to_oldpwd)
{
    char *env[] = {"HOME=/home/hic", "OLDPWD=/tmp", NULL};
    char **my_env = copy_env(env);
    char *args[] = {"cd", "-", NULL};
    char cwd[256];

    builtin_cd(args, &my_env);
    getcwd(cwd, 256);
    cr_assert_str_eq(cwd, "/tmp");
    free_env(my_env);
}

Test(builtin_cd, dash_without_oldpwd_returns_one)
{
    char *env[] = {"HOME=/home/hic", NULL};
    char **my_env = copy_env(env);
    char *args[] = {"cd", "-", NULL};
    int ret = builtin_cd(args, &my_env);

    cr_assert_eq(ret, 1);
    free_env(my_env);
}

Test(builtin_cd, updates_pwd_after_change)
{
    char *env[] = {"HOME=/home/hic", NULL};
    char **my_env = copy_env(env);
    char *args[] = {"cd", "/tmp", NULL};
    int i;
    int found = 0;

    builtin_cd(args, &my_env);
    for (i = 0; my_env[i] != NULL; i++) {
        if (my_strncmp(my_env[i], "PWD=/tmp", 8) == 0)
            found = 1;
    }
    cr_assert_eq(found, 1);
    free_env(my_env);
}

Test(builtin_env, returns_zero)
{
    char *env[] = {"PATH=/usr/bin", "HOME=/home/hic", NULL};
    int ret = builtin_env(env);

    cr_assert_eq(ret, 0);
}

Test(builtin_setenv, adds_new_variable)
{
    char *env[] = {"HOME=/home/hic", "USER=hic", NULL};
    char **my_env = copy_env(env);

    builtin_setenv((char *[]){"setenv", "MYVAR", "hello", NULL}, &my_env);
    cr_assert_str_eq(my_env[2], "MYVAR=hello");
    free_env(my_env);
}

Test(builtin_setenv, updates_existing_variable)
{
    char *env[] = {"HOME=/home/hic", "PATH=/usr/bin", NULL};
    char **my_env = copy_env(env);

    builtin_setenv((char *[]){"setenv", "PATH", "/tmp", NULL}, &my_env);
    cr_assert_str_eq(my_env[1], "PATH=/tmp");
    free_env(my_env);
}

Test(builtin_setenv, no_args_lists_env_and_returns_zero)
{
    char *env[] = {"HOME=/home/hic", NULL};
    char **my_env = copy_env(env);
    int ret = builtin_setenv((char *[]){"setenv", NULL}, &my_env);

    cr_assert_eq(ret, 0);
    free_env(my_env);
}

Test(builtin_setenv, too_many_args_returns_one)
{
    char *env[] = {"HOME=/home/hic", NULL};
    char **my_env = copy_env(env);
    int ret = builtin_setenv(
        (char *[]){"setenv", "FOO", "bar", "extra", NULL}, &my_env);

    cr_assert_eq(ret, 1);
    free_env(my_env);
}

Test(builtin_unsetenv, removes_existing_variable)
{
    char *env[] = {"HOME=/home/hic", "PATH=/usr/bin", "USER=hic", NULL};
    char **my_env = copy_env(env);

    builtin_unsetenv((char *[]){"unsetenv", "PATH", NULL}, my_env);
    cr_assert_str_eq(my_env[0], "HOME=/home/hic");
    cr_assert_str_eq(my_env[1], "USER=hic");
    cr_assert_null(my_env[2]);
    free_env(my_env);
}

Test(builtin_unsetenv, returns_no_error_on_unknown_variable)
{
    char *env[] = {"HOME=/home/hic", NULL};
    char **my_env = copy_env(env);
    int ret = builtin_unsetenv((char *[]){"unsetenv", "VARQUIEXISTEPAS", NULL}, my_env);

    cr_assert_eq(ret, 0);
    free_env(my_env);
}

Test(builtin_unsetenv, returns_error_without_args)
{
    char *env[] = {"HOME=/home/hic", NULL};
    char **my_env = copy_env(env);
    int ret = builtin_unsetenv((char *[]){"unsetenv", NULL}, my_env);

    cr_assert_neq(ret, 0);
    free_env(my_env);
}

Test(my_strcmp, equal_strings)
{
    cr_assert_eq(my_strcmp("abc", "abc"), 0);
}

Test(my_strcmp, different_strings)
{
    cr_assert_neq(my_strcmp("abc", "abd"), 0);
}

Test(my_strncmp, equal_prefix)
{
    cr_assert_eq(my_strncmp("hello", "help", 3), 0);
}

Test(my_strncmp, different_prefix)
{
    cr_assert_neq(my_strncmp("hello", "world", 3), 0);
}

Test(my_strcspn, finds_separator)
{
    cr_assert_eq(my_strcspn("abc|def", "|"), 3);
}

Test(my_strcspn, no_separator_returns_length)
{
    cr_assert_eq(my_strcspn("abcdef", "|"), 6);
}

Test(my_strdup, duplicates_string)
{
    char *dup = my_strdup("hello");

    cr_assert_str_eq(dup, "hello");
    free(dup);
}

Test(my_getnbr, parses_positive_number)
{
    cr_assert_eq(my_getnbr("42"), 42);
}

Test(my_getnbr, parses_negative_number)
{
    cr_assert_eq(my_getnbr("-42"), -42);
}

Test(my_getnbr, invalid_string_returns_zero)
{
    cr_assert_eq(my_getnbr("abc"), 0);
}

Test(shift_env, removes_middle_entry)
{
    char *env[] = {"A=1", "B=2", "C=3", NULL};

    shift_env(env, 1);
    cr_assert_str_eq(env[0], "A=1");
    cr_assert_str_eq(env[1], "C=3");
    cr_assert_null(env[2]);
}

Test(build_str, builds_key_value)
{
    char *args[] = {NULL, "FOO", "bar"};
    char *result = build_str(args);

    cr_assert_str_eq(result, "FOO=bar");
    free(result);
}

Test(build_str, builds_key_without_value)
{
    char *args[] = {NULL, "FOO", NULL};
    char *result = build_str(args);

    cr_assert_str_eq(result, "FOO=");
    free(result);
}

Test(if_not_found, appends_new_variable)
{
    char *env[] = {"HOME=/tmp", NULL};
    char **my_env = copy_env(env);
    char *args[] = {NULL, "FOO", "bar"};

    if_not_found(args, &my_env);
    cr_assert_str_eq(my_env[0], "HOME=/tmp");
    cr_assert_str_eq(my_env[1], "FOO=bar");
    cr_assert_null(my_env[2]);
    free_env(my_env);
}

Test(tabs_to_spaces, converts_tabs)
{
    char line[] = "a\tb\tc";

    tabs_to_spaces(line);
    cr_assert_str_eq(line, "a b c");
}

Test(free_args, handles_null_safely)
{
    free_args(NULL);
}

Test(is_builtin, recognizes_cd)
{
    char *env[] = {"HOME=/tmp", NULL};
    char **my_env = copy_env(env);
    char *args[] = {"cd", NULL};
    int exit_code = -1;
    int ret = is_builtin(&my_env, args, &exit_code);

    cr_assert_eq(ret, 1);
    cr_assert_eq(exit_code, 0);
    free_env(my_env);
}

Test(is_builtin, recognizes_env)
{
    char *env[] = {"HOME=/tmp", NULL};
    char **my_env = copy_env(env);
    char *args[] = {"env", NULL};
    int exit_code = -1;
    int ret = is_builtin(&my_env, args, &exit_code);

    cr_assert_eq(ret, 1);
    free_env(my_env);
}

Test(is_builtin, unknown_command_returns_zero)
{
    char *env[] = {"HOME=/tmp", NULL};
    char **my_env = copy_env(env);
    char *args[] = {"ls", NULL};
    int exit_code = -1;
    int ret = is_builtin(&my_env, args, &exit_code);

    cr_assert_eq(ret, 0);
    free_env(my_env);
}

Test(is_env_builtin, recognizes_setenv)
{
    char *env[] = {"HOME=/tmp", NULL};
    char **my_env = copy_env(env);
    char *args[] = {"setenv", "FOO", "bar", NULL};
    int exit_code = -1;
    int ret = is_env_builtin(&my_env, args, &exit_code);

    cr_assert_eq(ret, 1);
    cr_assert_eq(exit_code, 0);
    free_env(my_env);
}

Test(is_env_builtin, recognizes_unsetenv)
{
    char *env[] = {"HOME=/tmp", "FOO=bar", NULL};
    char **my_env = copy_env(env);
    char *args[] = {"unsetenv", "FOO", NULL};
    int exit_code = -1;
    int ret = is_env_builtin(&my_env, args, &exit_code);

    cr_assert_eq(ret, 1);
    free_env(my_env);
}

Test(exec_line, returns_zero_for_true)
{
    char *args[] = {"true", NULL};
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    int ret = exec_line(args, env);

    cr_assert_eq(ret, 0);
}

Test(exec_line, command_not_found_returns_one)
{
    char *args[] = {"commandquiexistepas42", NULL};
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    int ret = exec_line(args, env);

    cr_assert_eq(ret, 1);
}

Test(exec_separated, runs_all_segments_returns_last_exit_code)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char **my_env = copy_env(env);
    int exit_code = -1;
    char line[] = "true ; false";

    exec_separated(&my_env, line, &exit_code);
    cr_assert_neq(exit_code, 0);
    free_env(my_env);
}

Test(exec_separated, empty_segments_are_skipped)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char **my_env = copy_env(env);
    int exit_code = 0;
    char line[] = "true ;; true";

    exec_separated(&my_env, line, &exit_code);
    cr_assert_eq(exit_code, 0);
    free_env(my_env);
}

Test(exec_separated, cd_persists_across_segments)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char **my_env = copy_env(env);
    int exit_code = -1;
    char line[] = "cd /tmp ; cd -";
    char original[256];
    char cwd[256];

    getcwd(original, 256);
    exec_separated(&my_env, line, &exit_code);
    getcwd(cwd, 256);
    cr_assert_str_eq(cwd, original);
    free_env(my_env);
}

Test(exec_separated, segment_with_pipe_is_routed_to_pipe)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char **my_env = copy_env(env);
    int exit_code = -1;
    char line[] = "true | false ; true";

    exec_separated(&my_env, line, &exit_code);
    cr_assert_eq(exit_code, 0);
    free_env(my_env);
}

Test(exec_piped, simple_two_stage_pipe)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char **my_env = copy_env(env);
    int exit_code = -1;
    char segment[] = "true | true";

    exec_piped(&my_env, segment, &exit_code);
    cr_assert_eq(exit_code, 0);
    free_env(my_env);
}

Test(exec_piped, stage_pipe_returns_last_stage_status)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char **my_env = copy_env(env);
    int exit_code = -1;
    char segment[] = "false | true";

    exec_piped(&my_env, segment, &exit_code);
    cr_assert_eq(exit_code, 0);
    free_env(my_env);
}

Test(exec_piped, null_command_leading_pipe_returns_one)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char **my_env = copy_env(env);
    int exit_code = -1;
    char segment[] = "| wc -l";
    int ret = exec_piped(&my_env, segment, &exit_code);

    cr_assert_eq(ret, 1);
    cr_assert_eq(exit_code, 1);
    free_env(my_env);
}

Test(exec_piped, null_command_trailing_pipe_returns_one)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char **my_env = copy_env(env);
    int exit_code = -1;
    char segment[] = "ls |";
    int ret = exec_piped(&my_env, segment, &exit_code);

    cr_assert_eq(ret, 1);
    free_env(my_env);
}

Test(exec_piped, null_command_double_pipe_returns_one)
{
    char *env[] = {"PATH=/usr/bin:/bin", NULL};
    char **my_env = copy_env(env);
    int exit_code = -1;
    char segment[] = "ls | | wc -l";
    int ret = exec_piped(&my_env, segment, &exit_code);

    cr_assert_eq(ret, 1);
    free_env(my_env);
}

Test(apply_output_redirect, no_redirect_returns_zero)
{
    char **args = parse_args("echo hello");
    int saved_fd = -1;
    int ret = apply_output_redirect(args, &saved_fd);

    cr_assert_eq(ret, 0);
    cr_assert_eq(saved_fd, -1);
    free_args(args);
}

Test(apply_output_redirect, truncate_creates_and_writes_file)
{
    char **args = parse_args("echo hi > /tmp/mysh_redir_test1.txt");
    int saved_fd = -1;
    char buf[64];
    int fd;
    int len;

    unlink("/tmp/mysh_redir_test1.txt");
    apply_output_redirect(args, &saved_fd);
    write(STDOUT_FILENO, "content\n", 8);
    restore_output(saved_fd);
    fd = open("/tmp/mysh_redir_test1.txt", O_RDONLY);
    len = read(fd, buf, sizeof(buf) - 1);
    close(fd);
    buf[len] = '\0';
    cr_assert_str_eq(buf, "content\n");
    free_args(args);
}

Test(apply_output_redirect, removes_redirect_tokens_from_args)
{
    char **args = parse_args("echo hi > /tmp/mysh_redir_test2.txt");
    int saved_fd = -1;

    apply_output_redirect(args, &saved_fd);
    restore_output(saved_fd);
    cr_assert_str_eq(args[0], "echo");
    cr_assert_str_eq(args[1], "hi");
    cr_assert_null(args[2]);
    free_args(args);
}

Test(apply_output_redirect, append_mode_keeps_previous_content)
{
    char **args1 = parse_args("echo AAA > /tmp/mysh_redir_test3.txt");
    char **args2 = parse_args("echo BBB >> /tmp/mysh_redir_test3.txt");
    int saved_fd = -1;
    char buf[64];
    int fd;
    int len;

    unlink("/tmp/mysh_redir_test3.txt");
    apply_output_redirect(args1, &saved_fd);
    write(STDOUT_FILENO, "AAA\n", 4);
    restore_output(saved_fd);
    saved_fd = -1;
    apply_output_redirect(args2, &saved_fd);
    write(STDOUT_FILENO, "BBB\n", 4);
    restore_output(saved_fd);
    fd = open("/tmp/mysh_redir_test3.txt", O_RDONLY);
    len = read(fd, buf, sizeof(buf) - 1);
    close(fd);
    buf[len] = '\0';
    cr_assert_str_eq(buf, "AAA\nBBB\n");
    free_args(args1);
    free_args(args2);
}

Test(apply_output_redirect, invalid_directory_returns_minus_one)
{
    char **args = parse_args("echo hi > /nonexistentdir42/file.txt");
    int saved_fd = -1;
    int ret = apply_output_redirect(args, &saved_fd);

    cr_assert_eq(ret, -1);
    free_args(args);
}

Test(restore_output, does_nothing_with_negative_fd)
{
    restore_output(-1);
}

Test(build_path, builds_dir_slash_cmd)
{
    char *result = build_path("/usr/bin", "ls");

    cr_assert_str_eq(result, "/usr/bin/ls");
    free(result);
}

Test(drt_path, returns_path_for_existing_non_executable_file)
{
    char *result;

    unlink("/tmp/mysh_drt_test.txt");
    close(open("/tmp/mysh_drt_test.txt", O_WRONLY | O_CREAT, FILE_MODE));
    result = drt_path("/tmp/mysh_drt_test.txt");
    cr_assert_not_null(result);
    free(result);
}

Test(drt_path, returns_null_for_nonexistent_path)
{
    char *result = drt_path("/tmp/mysh_does_not_exist_xyz");

    cr_assert_null(result);
}

Test(search_in_dirs, finds_ls_in_path)
{
    char path[] = "/usr/bin:/bin";
    char *result = search_in_dirs(path, "ls");

    cr_assert_not_null(result);
    free(result);
}

Test(search_in_dirs, returns_null_when_not_found)
{
    char path[] = "/usr/bin:/bin";
    char *result = search_in_dirs(path, "commandquiexistepas42");

    cr_assert_null(result);
}

Test(find_home, changes_to_home_directory)
{
    char *env[] = {"HOME=/tmp", NULL};
    char **my_env = copy_env(env);
    char cwd[256];

    find_home(my_env, &my_env);
    getcwd(cwd, 256);
    cr_assert_str_eq(cwd, "/tmp");
    free_env(my_env);
}

Test(find_home, returns_zero_when_no_home_var)
{
    char *env[] = {"PATH=/usr/bin", NULL};
    char **my_env = copy_env(env);
    int ret = find_home(my_env, &my_env);

    cr_assert_eq(ret, 0);
    free_env(my_env);
}

Test(find_old, changes_to_oldpwd_directory)
{
    char *env[] = {"OLDPWD=/tmp", NULL};
    char **my_env = copy_env(env);
    char cwd[256];

    find_old(my_env, &my_env);
    getcwd(cwd, 256);
    cr_assert_str_eq(cwd, "/tmp");
    free_env(my_env);
}

Test(find_old, returns_one_without_oldpwd)
{
    char *env[] = {"HOME=/tmp", NULL};
    char **my_env = copy_env(env);
    int ret = find_old(my_env, &my_env);

    cr_assert_eq(ret, 1);
    free_env(my_env);
}

Test(get_git_branch, detects_branch_in_git_repo)
{
    char branch[128];
    int ret = get_git_branch(branch, sizeof(branch));

    cr_assert_eq(ret, 1);
    cr_assert(my_strlen(branch) > 0);
}

Test(get_git_branch, returns_zero_outside_git_repo)
{
    char branch[128];
    char cwd[256];
    int ret;

    getcwd(cwd, sizeof(cwd));
    chdir("/tmp");
    ret = get_git_branch(branch, sizeof(branch));
    chdir(cwd);
    cr_assert_eq(ret, 0);
}

Test(write_str, writes_full_string)
{
    int fds[2];
    char buf[32];
    int len;

    pipe(fds);
    write_str(fds[1], "hello");
    close(fds[1]);
    len = read(fds[0], buf, sizeof(buf) - 1);
    close(fds[0]);
    buf[len] = '\0';
    cr_assert_str_eq(buf, "hello");
}
