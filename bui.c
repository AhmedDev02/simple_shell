#include "shell.h"

// Function to exit the shell
int _mye(info_t *information)
{
    int exitcheck;

    if (information->argv[1]) // If there is an exit argument
    {
        exitcheck = _erratoi(information->argv[1]);
        if (exitcheck == -1)
        {
            information->status = 2;
            print_error(information, "Illegal number: ");
            _eputs(information->argv[1]);
            _eputchar('\n');
            return (1);
        }
        information->err_num = _erratoi(information->argv[1]);
        return (-2);
    }
    information->err_num = -1;
    return (-2);
}

// Function to change the current directory of the process
int _myc(info_t *information)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        _puts("getcwd failure emsg here\n");
    if (!information->argv[1])
    {
        dir = _getenv(information, "HOME=");
        if (!dir)
            chdir_ret = chdir((dir = _getenv(information, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp(information->argv[1], "-") == 0)
    {
        if (!_getenv(information, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(information, "OLDPWD=")), _putchar('\n');
        chdir_ret = chdir((dir = _getenv(information, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(information->argv[1]);
    if (chdir_ret == -1)
    {
        print_error(information, "can't cd to ");
        _eputs(information->argv[1]), _eputchar('\n');
    }
    else
    {
        _setenv(information, "OLDPWD", _getenv(information, "PWD="));
        _setenv(information, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

// Function to provide help (not yet implemented)
int _myh(info_t *information)
{
    char **arg_array;

    arg_array = information->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arg_array); // temp att_unused workaround
    return (0);
}
