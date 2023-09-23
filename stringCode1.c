#include "shell.h"

/**
 * _strcpy_info - Copies a string.
 * @dest: The destination.
 * @src: The source.
 *
 * Return: Pointer to destination.
 */
char *_strcpy_info(char *dest, char *src)
{
    int i = 0;

    if (dest == src || src == 0)
        return (dest);
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
    return (dest);
}

/**
 * _strdup_info - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *_strdup_info(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return (NULL);
    while (*str++)
        length++;
    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return (NULL);
    for (length++; length--;)
        ret[length] = *--str;
    return (ret);
}

/**
 * _puts_info - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts_info(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _putchar_info(str[i]);
        i++;
    }
}

/**
 * _putchar_info - Writes the character c to stdout.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar_info(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}
