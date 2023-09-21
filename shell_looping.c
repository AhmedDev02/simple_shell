#include "shell.h"
#define MY_NULL ((void *)0)

int shell_loop(information_t *information, char **arguments)
{
    ssize_t read_result = 0;
    int builtin_return = 0;

    while (read_result != -1 && builtin_return != -2)
    {
        clear_information(information);
        if (is_interactive(information))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        read_result = get_input(information);
        if (read_result != -1)
        {
            set_information(information, arguments);
            builtin_return = find_builtin_command(information);
            if (builtin_return == -1)
                find_shell_command(information);
        }
        else if (is_interactive(information))
            _putchar('\n');
        free_information(information, 0);
    }
    write_history(information);
    free_information(information, 1);
    if (!is_interactive(information) && information->status)
        exit(information->status);
    if (builtin_return == -2)
    {
        if (information->err_num == -1)
            exit(information->status);
        exit(information->err_num);
    }
    return (builtin_return);
}

int find_builtin_command(information_t *information)
{
    int i, builtin_return = -1;
    builtin_table builtintbl[] = {
        {"exit", my_exit_command},
        {"env", my_env_command},
        {"help", my_help_command},
        {"history", my_history_command},
        {"setenv", my_setenv_command},
        {"unsetenv", my_unsetenv_command},
        {"cd", my_cd_command},
        {"alias", my_alias_command},
        {MY_NULL, MY_NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
        if (_strcmp(information->argv[0], builtintbl[i].type) == 0)
        {
            information->line_count++;
            builtin_return = builtintbl[i].func(information);
            break;
        }
    return (builtin_return);
}

void find_shell_command(information_t *information)
{
    char *path = MY_NULL;
    int i, arg_count;

    information->path = information->argv[0];
    if (information->linecount_flag == 1)
    {
        information->line_count++;
        information->linecount_flag = 0;
    }
    for (i = 0, arg_count = 0; information->arg[i]; i++)
        if (!is_delimiter(information->arg[i], " \t\n"))
            arg_count++;
    if (!arg_count)
        return;

    path = find_path(information, _getenv(information, "PATH="), information->argv[0]);
    if (path)
    {
        information->path = path;
        fork_shell_command(information);
    }
    else
    {
        if ((is_interactive(information) || _getenv(information, "PATH=")
                    || information->argv[0][0] == '/') && is_shell_command(information, information->argv[0]))
            fork_shell_command(information);
        else if (*(information->arg) != '\n')
        {
            information->status = 127;
            print_error(information, "not found\n");
        }
    }
}

void fork_shell_command(information_t *information)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(information->path, information->argv, get_environment(information)) == -1)
        {
            free_information(information, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(information->status));
        if (WIFEXITED(information->status))
        {
            information->status = WEXITSTATUS(information->status);
            if (information->status == 126)
                print_error(information, "Permission denied\n");
        }
    }
}
