#include "shell.h"
/*
// Function to display the history list, one command by line, preceded
// with line numbers, starting at 0.
*/
int myhi(info_t *infop)
{
    print_list(infop->history);
    return (0);
}

// Function to unset alias
int unal(info_t *infop, char *strs)
{
    char *ptr, ch;
    int result;

    ptr = _strchr(strs, '=');
    if (!ptr)
        return (1);
    ch = *ptr;
    *ptr = 0;
    result = delete_node_at_index(&(infop->alias),
                                  get_node_index(infop->alias, node_starts_with(infop->alias, strs, -1)));
    *ptr = ch;
    return (result);
}

// Function to set alias
int sal(info_t *infop, char *strs)
{
    char *ptr;

    ptr = _strchr(strs, '=');
    if (!ptr)
        return (1);
    if (!*++ptr)
        return (unal(infop, strs));

    unal(infop, strs);
    return (add_node_end(&(infop->alias), strs, 0) == NULL);
}

// Function to print an alias string
int pral(list_t *nodep)
{
    char *ptr = NULL, *alias = NULL;

    if (nodep)
    {
        ptr = _strchr(nodep->str, '=');
        for (alias = nodep->str; alias <= ptr; alias++)
            _putchar(*alias);
        _putchar('\'');
        _puts(ptr + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

// Function to mimic the alias builtin (man alias)
int myal(info_t *infop)
{
    int i = 0;
    char *ptr = NULL;
    list_t *nodep = NULL;

    if (infop->argc == 1)
    {
        nodep = infop->alias;
        while (nodep)
        {
            pral(nodep);
            nodep = nodep->next;
        }
        return (0);
    }
    for (i = 1; infop->argv[i]; i++)
    {
        ptr = _strchr(infop->argv[i], '=');
        if (ptr)
            sal(infop, infop->argv[i]);
        else
            pral(node_starts_with(infop->alias, infop->argv[i], '='));
    }

    return (0);
}
