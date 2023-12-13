#include "shell.h"

/**
 * isInteractive - function that checks if shell is in interactive mode
 * @shellInfo: my struct address
 *
 * Return: returns 1 if in interactive mode, and 0 if otherwise
 */
int isInteractive(ShellInfo *shellInfo)
{
	return (isatty(STDIN_FILENO) && shellInfo->input_file_descriptor <= 2);
}

/**
 * isDelimiter - function that checks if the character is a delimiter
 * @character: the character to check
 * @delimiters: the delimiter's string
 *
 * Return: returns 1 if true, 0 if false
 */
int isDelimiter(char character, char *delimiters)
{
	while (*delimiters)
	{
		if (*delimiters++ == character)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * is_alpha - function that checks if character is alphabetic
 * @character: The character to be checked.
 *
 * Return: returns 1 if character is alphabetic, 0 if otherwise
 */
int is_alpha(int character)
{
	if ((character >= 'a' && character <= 'z') ||
	    (character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - function that converts a string to an integer
 * @stringToConvert: the string to be converted
 *
 * Return: returns 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *stringToConvert)
{
	int index = 0, sign = 1, flag = 0, output;
	unsigned int result = 0;

	while (stringToConvert[index] != '\0' && flag != 2)
	{
		if (stringToConvert[index] == '-')
			sign *= -1;

		if (stringToConvert[index] >= '0' && stringToConvert[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (stringToConvert[index] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}

		index++;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
