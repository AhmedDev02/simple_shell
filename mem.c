#include "shell.h"
// Frees a pointer and sets the address to NULL
int bfree(void **ptr)
{
    if (*ptr && *ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL;
        return (1);
    }
    return (0);
}

