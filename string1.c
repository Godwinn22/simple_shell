#include "shell.h"

/**
 * str_lengthgth - function that returns the string length.
 * @string: the string pointer
 *
 * Return: returns the length of string.
 */
int str_length(char *string)
{
	int len = 0;

	if (string == NULL)
		return (0);

	while (string[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * str_duplicate - function that duplicates a string
 * @string: the string to be copied
 *
 * Return: returns the pointer to the array
 */
char *str_duplicate(char *string)
{
	char *output;
	int len, i;

	if (string == NULL)
		return (NULL);

	len = str_length(string) + 1;

	output = malloc(sizeof(char) * len);

	if (output == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		output[i] = string[i];
		i++;
	}

	return (output);
}

/**
 * str_compare - function that Compare two strings
 * @str1: first string
 * @str2: second string
 * @num: the number of chars
 *
 * Return: returns 1 if the strings are equals,
 * 0 if the strings are different
 */
int str_compare(char *str1, char *string2, int num)
{
	int i;

	if (str1 == NULL && string2 == NULL)
		return (1);
	if (str1 == NULL || string2 == NULL)
		return (0);
	if (num == 0)
	{
		if (str_length(str1) != str_length(string2))
			return (0);
		for (i = 0; str1[i]; i++)
		{
			if (str1[i] != string2[i])
				return (0);
		}
		return (1);
	}
	else
	{
		for (i = 0; i < num; i++)
		{
			if (str1[i] != string2[i])
				return (0);
		}
		return (1);
	}
}

/**
 * str_concat - function that concatenates two strings.
 * @str1: first string to be concatenated
 * @str2: second string to be concatenated
 *
 * Return: returns pointer to an array
 */
char *str_concat(char *str1, char *str2)
{
	char *output;
	int len1 = 0, len2 = 0;

	if (str1 == NULL)
		str1 = "";
	len1 = str_length(str1);
	if (str2 == NULL)
		str2 = "";
	len2 = str_length(str2);
	output = malloc(sizeof(char) * (len1 + len2 + 1));
	if (output == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (len1 = 0; str1[len1] != '\0'; len1++)
		output[len1] = str1[len1];
	free(str1);
	for (len2 = 0; str2[len2] != '\0'; len2++)
	{
		output[len1] = str2[len2];
		len1++;
	}

	output[len1] = '\0';
	return (output);
}

/**
 * str_reverse - function that reverses a string.
 * @str: the pointer to string.
 *
 * Return: void.
 */
void str_reverse(char *str)
{

	int i = 0, len = str_length(str) - 1;
	char delay;

	while (i < len)
	{
		delay = str[i];
		str[i++] = str[len];
		str[len--] = delay;
	}
}
