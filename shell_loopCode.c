#include "shell.h"

/**
 * hsh_info - Main shell loop.
 * @info: The parameter & return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int hsh_info(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2)
    {
        clear_info(info);
        if (interactive_info(info))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        r = get_input_info(info);
        if (r != -1)
        {
            set_info_info(info, av);
            builtin_ret = find_builtin_info(info);
            if (builtin_ret == -1)
                find_cmd_info(info);
        }
        else if (interactive_info(info))
            _putchar('\n');
        free_info_info(info, 0);
    }
    write_history_info(info);
    free_info_info(info, 1);
    if (!interactive_info(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return (builtin_ret);
}

/**
 * find_builtin_info - Finds a builtin command.
 * @info: The parameter & return info struct.
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin_info(info_t *info)
{
    int i, built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit_info},
        {"env", _myenv_info},
        {"help", _myhelp_info},
        {"history", _myhistory_info},
        {"setenv", _mysetenv_info},
        {"unsetenv", _myunsetenv_info},
        {"cd", _mycd_info},
        {"alias", _myalias_info},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
        if (_strcmp_info(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    return (built_in_ret);
}

/**
 * find_cmd_info - Finds a command in PATH.
 * @info: The parameter & return info struct.
 *
 * Return: void
 */
void find_cmd_info(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
        if (!is_delim_info(info->arg[i], " \t\n"))
            k++;
    if (!k)
        return;

    path = find_path_info(info, _getenv_info(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_cmd_info(info);
    }
    else
    {
        if ((interactive_info(info) || _getenv_info(info, "PATH=")
                || info->argv[0][0] == '/') && is_cmd_info(info, info->argv[0]))
            fork_cmd_info(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error_info(info, "not found\n");
        }
    }
}

/**
 * fork_cmd_info - Forks a an exec thread to run cmd.
 * @info: The parameter & return info struct.
 *
 * Return: void
 */
void fork_cmd_info(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environ_info(info)) == -1)
        {
            free_info_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
        /* TODO: PUT ERROR FUNCTION */
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error_info(info, "Permission denied\n");
        }
    }
}
