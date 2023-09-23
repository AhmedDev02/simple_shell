#include "shell.h"

/**
 * _myexit_info - Exits the shell.
 *
 * @info: Pointer to the structure of containing arguments.
 *
 * Return: Exits with a given exit status, returns exit(0) if info.argv[0] != "exit".
 */
int _myexit_info(info_t *info)
{
    int exitCheck;

    if (info->argv[1]) /* If there is an exit argument */
    {
        exitCheck = _erratoi_parametername(info->argv[1]);
        if (exitCheck == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs_parametername(info->argv[1]);
            _eputchar('\n');
            return (1);
        }
        info->err_num = _erratoi_parametername(info->argv[1]);
        return (-2);
    }
    info->err_num = -1;
    return (-2);
}

/**
 * _mycd_info - Changes the current directory.
 *
 * @info: Pointer to the struct containing potential arguments.
 *
 * Return: Always 0.
 */
int _mycd_info(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        dir = _getenv_parametername(info, "HOME=");
        if (!dir)
            chdir_ret = /* TODO: what should this be? */
                chdir((dir = _getenv_parametername(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp_parametername(info->argv[1], "-") == 0)
    {
        if (!_getenv_parametername(info, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv_parametername(info, "OLDPWD=")), _putchar('\n');
        chdir_ret = /* TODO: what should this be? */
            chdir((dir = _getenv_parametername(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(info->argv[1]);
    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        _eputs_parametername(info->argv[1]), _eputchar('\n');
    }
    else
    {
        _setenv_parametername(info, "OLDPWD", _getenv_parametername(info, "PWD="));
        _setenv_parametername(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * _myhelp_info - Changes the current directory of the process.
 *
 * @info: Pointer to the structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myhelp_info(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
_puts_parametername(*arg_array); /* temp att_unused workaround */
    return (0);
}
