#include "shell.h"

/**
 * _myhistory_info - Displays the history list, one command by line, preceded
 *                   with line numbers, starting at 0.
 * @info: Pointer to the structure of containing arguments.
 *
 * Return: Always returns 0.
 */
int _myhistory_info(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_alias_info - Sets alias to string.
 * @info: Pointer to the parameter structure.
 * @str: String alias.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int unset_alias_info(info_t *info, char *str)
{
    char *q, s;
    int ret;

    q = _strchr(str, '=');
    if (!q)
        return (1);
    s = *q;
    *q = 0;
    ret = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *q = s;
    return (ret);
}

/**
 * set_alias_info - Sets alias to string.
 * @info: Pointer to the parameter structure.
 * @str: String alias.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int set_alias_info(info_t *info, char *str)
{
    char *q;

    q = _strchr(str, '=');
    if (!q)
        return (1);
    if (!*++q)
        return (unset_alias_info(info, str));

    unset_alias_info(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias_info - Prints an alias string.
 * @node: Alias node.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int print_alias_info(list_t *node)
{
    char *q = NULL, *b = NULL;

    if (node)
    {
        q = _strchr(node->str, '=');
        for (b = node->str; b <= q; b++)
            _putchar(*b);
        _putchar('\'');
        _puts(q + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * _myalias_info - Mimics the alias builtin (man alias).
 * @info: Pointer to the structure containing arguments.
 *
 * Return: Always returns 0.
 */
int _myalias_info(info_t *info)
{
    int i = 0;
    char *q = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias_info(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        q = _strchr(info->argv[i], '=');
        if (q)
            set_alias_info(info, info->argv[i]);
        else
            print_alias_info(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
