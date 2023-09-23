#include "shell.h"

/**
 * bfree_info - Frees a pointer and NULLs the address.
 * @_ptr: Address of the pointer to free.
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree_info(void **_ptr)
{
    if (_ptr && *_ptr)
    {
        free(*_ptr);
        *_ptr = NULL;
        return (1);
    }
    return (0);
}
