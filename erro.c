#include "shell.h"

// Function to print the current environment
int myen(info_t *infop)
{
    print_list_str(infop->env);
    return (0);
}

// Function to get the value of an environment variable
char *gete(info_t *infop, const char *name)
{
    list_t *node = infop->env;
    char *ptr;

    while (node)
    {
        ptr = starts_with(node->str, name);
        if (ptr && *ptr)
            return (ptr);
        node = node->next;
    }
    return (NULL);
}

// Function to initialize a new environment variable or modify an existing one
int myse(info_t *infop)
{
    if (infop->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (sete(infop, infop->argv[1], infop->argv[2]))
        return (0);
    return (1);
}

// Function to remove an environment variable
int myun(info_t *infop)
{
    int i;

    if (infop->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= infop->argc; i++)
        unsete(infop, infop->argv[i]);

    return (0);
}

// Function to populate the environment linked list
int popu(info_t *infop)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; infop->environ[i]; i++)
        add_node_end(&node, infop->environ[i], 0);
    infop->env = node;
    return (0);
}
