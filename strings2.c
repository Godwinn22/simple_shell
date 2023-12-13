#include "shell.h"

/**
 * _putchar - a function that writes the character c to the stdout
 * @characterToPrint: The character to print
 *
 * Return: returns On success 1.
 * On error, -1 is returned, and the errno is set appropriately.
 */
int _putchar(char characterToPrint)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (characterToPrint == BUFFER_CLEAR || i >= BUFFER_SIZE_WRITE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (characterToPrint != BUFFER_CLEAR)
		buf[i++] = characterToPrint;
	return (1);
}

/**
 * *_strn_cpy - function that copies a string
 * from source to destination.
 * @destStr: the destination string to be copied to
 * @srcStr: the source string
 * @numberOfCharacters: the amount of characters to be copied
 *
 * Return: returns the concatenated string
 */
char *_strn_cpy(char *destStr, char *srcStr, int numberOfCharacters)
{
	int index = 0, j;
	char *s = destStr;

	for (; srcStr[index] != '\0' && index < numberOfCharacters - 1; index++)
	{
		destStr[index] = srcStr[index];
	}
	if (index < numberOfCharacters)
	{
		j = index;
		for (; j < numberOfCharacters; j++)
		{
			destStr[j] = '\0';
		}
	}
	return (s);
}

/**
 * *_strn_cat - a function that concatenates two strings
 * @destStr: the first string
 * @srcStr: the second string
 * @numberOfCharacters: the amount of bytes to be maximally used
 *
 * Return: returns the concatenated string
 */
char *_strn_cat(char *destStr, char *srcStr, int numberOfCharacters)
{
	int index, j;
	char *s = destStr;

	index = 0;
	j = 0;
	while (destStr[index] != '\0')
		index++;
	while (srcStr[j] != '\0' && j < numberOfCharacters)
	{
		destStr[index] = srcStr[j];
		index++;
		j++;
	}
	if (j < numberOfCharacters)
		destStr[index] = '\0';
	return (s);
}

/**
 * *_str_chr - a function that locates a character in a string
 * @stringToSearch: the string to be parsed
 * @characterToFind: the character to look for
 *
 * Return: returns a pointer to the memory area stringToSearch
 */
char *_str_chr(char *stringToSearch, char characterToFind)
{
	do {
		if (*stringToSearch == characterToFind)
			return (stringToSearch);
	} while (*stringToSearch++ != '\0');

	return (NULL);
}

/**
 * _puts - a function that prints an input string
 * @stringToPrint: the string to be printed out
 *
 * Return: void
 */
void _puts(char *stringToPrint)
{
	int i = 0;

	if (!stringToPrint)
		return;
	for (; stringToPrint[i] != '\0'; i++)
	{
		_putchar(stringToPrint[i]);
	}
}
