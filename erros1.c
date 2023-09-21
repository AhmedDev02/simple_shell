#include "shell.h"

// _erro - converts a string to an integer, @str: the string to be converted, Return: 0 if no numbers in string, converted number otherwise, -1 on error
int _erro(char *str)
{
    int i = 0;
    unsigned long int result = 0;

    if (*str == '+')
        str++;
    for (i = 0;  str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            result *= 10;
            result += (str[i] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (result);
}

// perr - prints an error message, @information: the parameter & return info struct, @estr: string containing specified error type, Return: 0 if no numbers in string, converted number otherwise, -1 on error
void perr(info_t *information, char *estr)
{
    _eputs(information->fname);
    _eputs(": ");
    print_d(information->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(information->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

// prdi - function prints a decimal (integer) number (base 10), @input: the input, @fd: the filedescriptor to write to, Return: number of characters printed
int prdi(int input, int fd)
{
    int (*__putchar)(char) = _putchar;
    int i, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        __putchar = _eputchar;
    if (input < 0)
    {
        _abs_ = -input;
        __putchar('-');
        count++;
    }
    else
        _abs_ = input;
    current = _abs_;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }
    __putchar('0' + current);
    count++;

    return (count);
}

// conu - converter function, a clone of itoa, @num: number, @base: base, @flags: argument flags, Return: string
char *conu(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }
    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return (ptr);
}

// remc - function replaces first instance of '#' with '\0', @buf: address of the string to modify, Return: Always 0;
void remc(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
}