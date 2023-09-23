#include "shell.h"

/**
 * _strlen_info - Returns the length of a string.
 * @_s: The string whose length to check.
 *
 * Return: Integer length of the string.
 */
int _strlen_info(char *_s)
{
    int i = 0;

    if (!_s)
        return (0);

    while (*_s++)
        i++;
    return (i);
}

/**
 * _strcmp_info - Performs lexicographic comparison of two strings.
 * @_s1: The first string.
 * @_s2: The second string.
 *
 * Return: Negative if @_s1 < @_s2, positive if @_s1 > @_s2, zero if @_s1 == @_s2.
 */
int _strcmp_info(char *_s1, char *_s2)
{
    while (*_s1 && *_s2)
    {
        if (*_s1 != *_s2)
            return (*_s1 - *_s2);
        _s1++;
        _s2++;
    }
    if (*_s1 == *_s2)
        return (0);
    else
        return (*_s1 < *_s2 ? -1 : 1);
}

/**
 * starts_with_info - Checks if needle starts with haystack.
 * @haystack: String to search.
 * @needle: The substring to find.
 *
 * Return: Address of the next character of haystack or NULL.
 */
char *starts_with_info(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return (NULL);
    return ((char *)haystack);
}

/**
 * _strcat_info - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcat_info(char *dest, char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return (ret);
}
