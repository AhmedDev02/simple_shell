#include "shell.h"

// Returns the length of a string.
int _strlen(char *str)
{
    int length = 0;

    if (!str)
        return (0);

    while (*str++)
        length++;
    return (length);
}

// Performs lexicographic comparison of two strings.
int _strcmp(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);
        str1++;
        str2++;
    }
    if (*str1 == *str2)
        return (0);
    else
        return (*str1 < *str2 ? -1 : 1);
}

// Checks if one string starts with another.
char *starts_with(const char *main_str, const char *prefix)
{
    while (*prefix)
        if (*prefix++ != *main_str++)
            return (NULL);
    return ((char *)main_str);
}

// Concatenates two strings.
char *_strcat(char *destination, char *source)
{
    char *result = destination;

    while (*destination)
        destination++;
    while (*source)
        *destination++ = *source++;
    *destination = *source;
    return (result);
}
