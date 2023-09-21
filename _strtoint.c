#include "shell.h"

// Function to check if the shell is in interactive mode
int interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

// Function to check if a character is a delimiter
int deli(char character, char *delimiter)
{
    while (*delimiter)
        if (*delimiter++ == character)
            return (1);
    return (0);
}

// Function to check if a character is alphabetic
int _alph(int character)
{
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
        return (1);
    else
        return (0);
}

// Function to convert a string to an integer
int _strtoint(char *string)
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; string[i] != '\0' && flag != 2; i++)
    {
        if (string[i] == '-')
            sign *= -1;

        if (string[i] >= '0' && string[i] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (string[i] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    if (sign == -1)
        output = -result;
    else
        output = result;

    return (output);
}
