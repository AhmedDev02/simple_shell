#include "shell.h"

/**
 * _memset_info - Fills memory with a constant byte.
 * @_s: The pointer to the memory area.
 * @_b: The byte to fill @_s with.
 * @_n: The amount of bytes to be filled.
 * Return: (@_s) A pointer to the memory area @_s.
 */
char *_memset_info(char *_s, char _b, unsigned int _n)
{
    unsigned int _i;

    for (_i = 0; _i < _n; _i++)
        _s[_i] = _b;
    return (_s);
}

/**
 * ffree_info - Frees a string of strings.
 * @_pp: String of strings.
 */
void ffree_info(char **_pp)
{
    char **_a = _pp;

    if (!_pp)
        return;
    while (*_pp)
        free(*_pp++);
    free(_a);
}

/**
 * _realloc_info - Reallocates a block of memory.
 * @_ptr: Pointer to the previous malloc'ated block.
 * @_old_size: Byte size of the previous block.
 * @_new_size: Byte size of the new block.
 *
 * Return: Pointer to da ol'block nameen.
 */
void *_realloc_info(void *_ptr, unsigned int _old_size, unsigned int _new_size)
{
    char *_p;

    if (!_ptr)
        return (malloc(_new_size));
    if (!_new_size)
        return (free(_ptr), NULL);
    if (_new_size == _old_size)
        return (_ptr);

    _p = malloc(_new_size);
    if (!_p)
        return (NULL);

    _old_size = _old_size < _new_size ? _old_size : _new_size;
    while (_old_size--)
        _p[_old_size] = ((char *)_ptr)[_old_size];
    free(_ptr);
    return (_p);
}
