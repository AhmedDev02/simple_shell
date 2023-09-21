#include "shell.h"

// Function to print an input string to stderr
void epu(char *strrs)
{
    int integer = 0;

    if (!strrs)
        return;
    while (strrs[integer] != '\0')
    {
        epuc(strrs[integer]);
        integer++;
    }
}

// Function to write the character c to stderr
int epuc(char car)
{
    static int integer;
    static char buf[WRITE_BUF_SIZE];

    if (car == BUF_FLUSH || integer >= WRITE_BUF_SIZE)
    {
        write(2, buf, integer);
        integer = 0;
    }
    if (car != BUF_FLUSH)
        buf[integer++] = car;
    return (1);
}

// Function to write the character c to the given file descriptor
int pufd(char car, int fd)
{
    static int integer;
    static char buf[WRITE_BUF_SIZE];

    if (car == BUF_FLUSH || integer >= WRITE_BUF_SIZE)
    {
        write(fd, buf, integer);
        integer = 0;
    }
    if (car != BUF_FLUSH)
        buf[integer++] = car;
    return (1);
}

// Function to print an input string to the given file descriptor
int pusfd(char *strrs, int fd)
{
    int integer = 0;

    if (!strrs)
        return (0);
    while (*strrs)
    {
        integer += pufd(*strrs++, fd);
    }
    return (integer);
}
