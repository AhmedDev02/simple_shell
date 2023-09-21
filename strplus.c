#include "shell.h"

/* Copies a string */
char *_strcpy(char *dest, char *strr)
{
    int i = 0;

    if (dest == strr || strr == MY_NULL)
        return (dest);
    while (strr[i])
    {
        dest[i] = strr[i];
        i++;
    }
    dest[i] = 0;
    return (dest);
}

/* Duplicates a string */
char *_strdup(const char *strr)
{
    int length = 0;
    char *ret;

    if (strr == MY_NULL)
        return (MY_NULL);
    while (*strr++)
        length++;
    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return (MY_NULL);
    for (length++; length--;)
        ret[length] = *--strr;
    return (ret);
}

/* Prints an input string */
void _puts(char *strr)
{
    int i = 0;

    if (!strr)
        return;
    while (strr[i] != '\0')
    {
        _putchar(strr[i]);
        i++;
    }
}

/* Writes a character to stdout */
int _putchar(char c)
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
