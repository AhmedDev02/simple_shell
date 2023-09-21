#include "shell.h"

#define MY_NULL (void *)0

// Determines length of linked list
size_t _list_len(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        h = h->next;
        i++;
    }
    return (i);
}

// Returns an array of strings of the list->str
char **_list_to_strings(list_t *head)
{
    list_t *node = head;
    size_t i = _list_len(head), j;
    char **strs;
    char *str;

    if (!head || !i)
        return (MY_NULL);
    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (MY_NULL);
    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (MY_NULL);
        }

        str = _strcpy(str, node->str);
        strs[i] = str;
    }
    strs[i] = MY_NULL;
    return (strs);
}

// Prints all elements of a list_t linked list
size_t _print_list(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(convert_number(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }
    return (i);
}

// Returns node whose string starts with prefix
list_t *_node_starts_with(list_t *node, char *prefix, char c)
{
    char *p = MY_NULL;

    while (node)
    {
        p = _starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return (node);
        node = node->next;
    }
    return (MY_NULL);
}

// Gets the index of a node
ssize_t _get_node_index(list_t *head, list_t *node)
{
    size_t i = 0;

    while (head)
    {
        if (head == node)
            return (i);
        head = head->next;
        i++;
    }
    return (-1);
}

