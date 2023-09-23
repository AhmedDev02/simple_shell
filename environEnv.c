#include "shell.h"

/**
 * _myenv_info - Prints the current environment.
 * @info: Pointer to the structure of containing arguments.
 *
 * Return: Always returns 0.
 */
int _myenv_info(info_t *info)
{
    print_list_str(info->env);
    return (0);
}

/**
 * _getenv_info - Gets the value of an environment variable.
 * @info: Pointer to the structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Return: Returns the value of the environment variable or NULL if not found.
 */
char *_getenv_info(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *q;

    while (node)
    {
        q = starts_with(node->str, name);
        if (q && *q)
            return (q);
        node = node->next;
    }
    return (NULL);
}

/**
 * _mysetenv_info - Initializes a new environment variable or modifies an existing one.
 * @info: Pointer to the structure containing potential arguments.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int _mysetenv_info(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (_setenv(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * _myunsetenv_info - Removes an environment variable.
 * @info: Pointer to the structure containing potential arguments.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int _myunsetenv_info(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * populate_env_list_info - Populates the environment linked list.
 * @info: Pointer to the structure containing potential arguments.
 *
 * Return: Always returns 0.
 */
int populate_env_list_info(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;
    return (0);
}
