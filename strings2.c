#include "shell.h"

/**
 * long_to_string - function converts a number to string.
 * @number: number to be converted to string.
 * @string: buffer to save the  number as string.
 * @base: base to convert to
 *
 * Return: void.
 */
void long_to_string(long number, char *string, int base)
{
	int i = 0, is_negative = 0;
	long quotient = number;
	char letters[] = {"0123456789abcdef"};

	if (quotient == 0)
		string[i++] = '0';

	if (string[0] == '-')
		is_negative = 1;

	while (quotient)
	{
		if (quotient < 0)
			string[i++] = letters[-(quotient % base)];
		else
			string[i++] = letters[quotient % base];
		quotient /= base;
	}
	if (is_negative)
		string[i++] = '-';

	string[i] = '\0';
	str_reverse(string);
}


/**
 * _atoi - function that convert a string to an integer in ascii.
 * @s: the pointer to string origin.
 * 
 * Return: returns the integer of string or 0.
 */
int _atoi(char *s)
{
	int operand = 1;
	unsigned int num = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			operand *= -1;
		if (*s == '+')
			operand *= +1;
		s++;
	}

	for (; '0' <= *s && *s <= '9' && *s != '\0'; s++)
	{

		num = (num * 10) + (*s - '0');
	}
	return (num * operand);
}

/**
 * count_characters - function that counts the number of string character
 * @str: pointer to string origin.
 * @chars: string with  chars to be counted
 * 
 * Return: returns the integer of string or 0.
 */
int count_characters(char *str, char *chars)
{
	int i = 0, count = 0;

	while (str[i])
	{
		if (str[i] == chars[0])
			count++;
		i++;
	}
	return (count);
}
