#include "shell.h"

/**
 * **_strtow - function that splits a string into words.
 * Repeat delimiters are ignored
 * @inputString: the input string
 * @delimiters: the delimeter string
 *
 * Return: returns a pointer to an array of strings, or NULL on failure
 */
char **_strtow(char *inputString, char *delimiters)
{

	int index, j, k, m, num_of_words = 0;
	char **splitString;

	if (inputString == NULL || inputString[0] == 0)
		return (NULL);
	if (!delimiters)
		delimiters = " ";
	for (index = 0; inputString[index] != '\0'; index++)
		if (!isDelimiter(inputString[index], delimiters) &&
		    (isDelimiter(inputString[index + 1], delimiters) ||
		     !inputString[index + 1]))
			num_of_words++;
	if (num_of_words == 0)
		return (NULL);
	splitString = malloc((1 + num_of_words) * sizeof(char *));
	if (!splitString)
		return (NULL);
	for (index = 0, j = 0; j < num_of_words; j++)
	{
		while (isDelimiter(inputString[index], delimiters))
			index++;
		k = 0;
		while (!isDelimiter(inputString[index + k], delimiters) &&
		       inputString[index + k])
			k++;
		splitString[j] = malloc((k + 1) * sizeof(char));
		if (!splitString[j])
		{
			for (k = 0; k < j; k++)
				free(splitString[k]);
			free(splitString);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			splitString[j][m] = inputString[index++];
		splitString[j][m] = 0;
	}
	splitString[j] = NULL;
	return (splitString);
}

/**
 * **_strn_tow - function that splits a string into words
 * @inputString: the input string
 * @delimiter: the delimeter
 *
 * Return: returns a pointer to an array of strings, or NULL on failure
 */
char **_strn_tow(char *inputString, char delimiter)
{
	int index, j, k, m, num_of_words = 0;
	char **splitString;

	if (inputString == NULL || inputString[0] == 0)
		return (NULL);
	for (index = 0; inputString[index] != '\0'; index++)
		if ((inputString[index] != delimiter && inputString[index + 1]
			== delimiter) || (inputString[index] != delimiter &&
			!inputString[index + 1]) || inputString[index + 1] == delimiter)
			num_of_words++;
	if (num_of_words == 0)
		return (NULL);
	splitString = malloc((1 + num_of_words) * sizeof(char *));
	if (!splitString)
		return (NULL);
	for (index = 0, j = 0; j < num_of_words; j++)
	{
		while (inputString[index] == delimiter && inputString[index] != delimiter)
			index++;
		k = 0;
		while (inputString[index + k] != delimiter &&
		       inputString[index + k] && inputString[index + k] != delimiter)
			k++;
		splitString[j] = malloc((k + 1) * sizeof(char));
		if (!splitString[j])
		{
			k = 0;
			while (k < j)
			{
				free(splitString[k]);
				k++;
			}
			free(splitString);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			splitString[j][m] = inputString[index++];
		splitString[j][m] = 0;
	};
	splitString[j] = NULL;
	return (splitString);
}
