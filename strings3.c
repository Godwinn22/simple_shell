#include "shell.h"

/**
 * *strn_cpy - copies a string from source to destination
 * @destStr: the destination string
 * @srcStr: the source string
 *
 * Return: returns a pointer to the destination string
 */
char *strn_cpy(char *destStr, char *srcStr)
{
	int index = 0;

	if (destStr == srcStr || srcStr == NULL)
		return (destStr);
	while (srcStr[index])
	{
		destStr[index] = srcStr[index];
		index++;
	}
	destStr[index] = '\0';
	return (destStr);
}

/**
 * *strn_dup - function that duplicates a string
 * @stringToDuplicate: the string to be duplicated
 *
 * Return: returns a pointer to the duplicated string
 */
char *strn_dup(const char *stringToDuplicate)
{
	int length = 0;
	char *retstrn;

	if (stringToDuplicate == NULL)
		return (NULL);
	while (*stringToDuplicate++)
		length++;
	retstrn = malloc(sizeof(char) * (length + 1));
	if (!retstrn)
		return (NULL);
	for (length++; length--;)
		retstrn[length] = *--stringToDuplicate;
	return (retstrn);
}
