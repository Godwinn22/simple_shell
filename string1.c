#include "shell.h"

/**
 * strn_len - function that checks for the length of a string
 * @inputString: the string whose length to check
 *
 * Return: returns the length of the string
 */
int strn_len(char *inputString)
{
	int length = 0;

	if (!inputString)
		return (0);
	for (; *inputString++; length++)
		;
	return (length);
}

/**
 * str_cmp - function that performs comparison between two strings
 * @string1: the first string
 * @string2: the second string
 *
 * Return: returns negative if string1 < string2,
 * positive if string1 > string2, zero if string1 == string2
 */
int str_cmp(char *string1, char *string2)
{
	for (; *string1 && *string2; string1++, string2++)
	{
		if (*string1 != *string2)
		{
			return (*string1 - *string2);
		}
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * *startsWith - checks if fullString starts with substring
 * @fullString: the string to search
 * @substring: the substring to find
 *
 * Return: returns the address of next character of fullString or NULL
 */
char *startsWith(const char *fullString, const char *substring)
{
	for (; *substring; substring++, fullString++)
	{
		if (*substring != *fullString)
			return (NULL);
	}
	return ((char *)fullString);
}

/**
 * *strn_cat - function that concatenates two strings
 * @destStr: the destination buffer
 * @srcStr: the source buffer
 *
 * Return: returns the pointer to destination buffer
 */
char *strn_cat(char *destStr, char *srcStr)
{
	char *returnPointer = destStr;

	for (; *destStr; destStr++)
		;
	for (; *srcStr; *destStr++ = *srcStr++)
		;
	*destStr = *srcStr;
	return (returnPointer);
}
