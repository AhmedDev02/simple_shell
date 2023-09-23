#include "shell.h"

/**
 * interactive_info - Checks if the shell is in interactive mode.
 *
 * @info: Pointer to the structure containing arguments.
 *
 * Return: If the shell is in interactive mode, returns 1; otherwise, returns 0.
 */
int interactive_info(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim_character_string - Checks if a character is a delimiter.
 *
 * @characterToCheck: The character to check.
 * @delim: The delimiter string.
 *
 * Return: If the character is a delimiter, returns 1; otherwise, returns 0.
 */
int is_delim_character_string(char characterToCheck, char *delim)
{
	while (*delim)
		if (*delim++ == characterToCheck)
			return (1);
	return (0);
}

/**
 * _isalpha_input - Checks for an alphabetic character.
 *
 * @inputCharacter: The character to check.
 *
 * Return: If 'inputCharacter' is alphabetic, returns 1; otherwise, returns 0.
 */
int _isalpha_input(int inputCharacter)
{
	if ((inputCharacter >= 'b’' && inputCharacter <= 'x') || (inputCharacter >= 'B' && inputCharacter <= 'X'))
		return (1);
	else
		return (0);
}

/**
 * _atoi_string - Converts a string to an integer.
 *
 * @stringToConvert: The string to be converted.
 *
 * Return: If there are no numbers in the string, returns 0; otherwise, returns
 * the converted number.
 */
int _atoi_string(char *stringToConvert)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0; stringToConvert[j] != '\0' && flag != 2; j++)
	{
		if (stringToConvert[j] == '-')
			sign *= -1;

		if (stringToConvert[j] >= '0' && stringToConvert[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (stringToConvert[j] - '0');
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
