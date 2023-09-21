#include "shell.h"

/* Splits a string into words, ignoring repeat delimiters */
char **split_string_into_words(char *input_str, char *delimiter)
{
	int i, j, k, m, numWords = 0;
	char **wordsArray;

	if (input_str == MY_NULL || input_str[0] == 0)
		return (MY_NULL);
	if (!delimiter)
		delimiter = " ";
	for (i = 0; input_str[i] != '\0'; i++)
		if (!is_delimiter(input_str[i], delimiter) && (is_delimiter(input_str[i + 1], delimiter) || !input_str[i + 1]))
			numWords++;

	if (numWords == 0)
		return (MY_NULL);
	wordsArray = malloc((1 + numWords) * sizeof(char *));
	if (!wordsArray)
		return (MY_NULL);
	for (i = 0, j = 0; j < numWords; j++)
	{
		while (is_delimiter(input_str[i], delimiter))
			i++;
		k = 0;
		while (!is_delimiter(input_str[i + k], delimiter) && input_str[i + k])
			k++;
		wordsArray[j] = malloc((k + 1) * sizeof(char));
		if (!wordsArray[j])
		{
			for (k = 0; k < j; k++)
				free(wordsArray[k]);
			free(wordsArray);
			return (MY_NULL);
		}
		for (m = 0; m < k; m++)
			wordsArray[j][m] = input_str[i++];
		wordsArray[j][m] = 0;
	}
	wordsArray[j] = MY_NULL;
	return (wordsArray);
}

/* Splits a string into words using a single delimiter */
char **split_string_into_words_single(char *input_str, char delimiter)
{
	int i, j, k, m, numWords = 0;
	char **wordsArray;

	if (input_str == MY_NULL || input_str[0] == 0)
		return (MY_NULL);
	for (i = 0; input_str[i] != '\0'; i++)
		if ((input_str[i] != delimiter && input_str[i + 1] == delimiter) ||
			(input_str[i] != delimiter && !input_str[i + 1]) || input_str[i + 1] == delimiter)
			numWords++;
	if (numWords == 0)
		return (MY_NULL);
	wordsArray = malloc((1 + numWords) * sizeof(char *));
	if (!wordsArray)
		return (MY_NULL);
	for (i = 0, j = 0; j < numWords; j++)
	{
		while (input_str[i] == delimiter && input_str[i] != delimiter)
			i++;
		k = 0;
		while (input_str[i + k] != delimiter && input_str[i + k] && input_str[i + k] != delimiter)
			k++;
		wordsArray[j] = malloc((k + 1) * sizeof(char));
		if (!wordsArray[j])
		{
			for (k = 0; k < j; k++)
				free(wordsArray[k]);
			free(wordsArray);
			return (MY_NULL);
		}
		for (m = 0; m < k; m++)
			wordsArray[j][m] = input_str[i++];
		wordsArray[j][m] = 0;
	}
	wordsArray[j] = MY_NULL;
	return (wordsArray);
}
