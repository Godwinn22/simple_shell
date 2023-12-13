#include "shell.h"

/**
 * printDecimal - function prints a decimal (integer) number (base 10)
 * @numToPrint: the number to print
 * @fileDescriptor: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int printDecimal(int numToPrint, int fileDescriptor)
{
	int (*printChar)(char) = _putchar;
	int i, counter = 0;
	unsigned int absNum, currentNum;

	if (fileDescriptor == STDERR_FILENO)
		printChar = e_putchar;
	if (numToPrint < 0)
	{
		absNum = -numToPrint;
		printChar('-');
		counter++;
	}
	else
		absNum = numToPrint;
	currentNum = absNum;
	i = 1000000000;
	while (i > 1)
	{
		if (absNum / i)
		{
			printChar('0' + currentNum / i);
			counter++;
		}
		currentNum = currentNum % i;
		i = i / 10;
	}

	printChar('0' + currentNum);
	counter++;

	return (counter);
}

/**
 * convertToBase - converts a number to a string in the specified base
 * @number: the number to convert
 * @base: the base for conversion
 * @flags: formatting flags
 *
 * Return: string representation of number
 */
char *convertNum(long int number, int base, int flags)
{
	static char *digits;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flags & CONVERT_TO_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = 45;
	}

	digits = flags & CONVERT_TO_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = digits[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * stripComments - removes the first instance of '#' and everything after it
 * @buffer: the string to modify
 *
 * Return: Always 0;
 */
void stripComments(char *buffer)
{
	int i = 0;

	while (buffer[i] != '\0')
	{
		if (buffer[i] == 35 && (!i || buffer[i - 1] == 32))
		{
			buffer[i] = '\0';
			break;
		}
		i++;
	}
}

/**
 * printError - prints an error message
 * @shellInfo: the parameter & return info struct
 * @errorStr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void printError(ShellInfo *shellInfo, char *errorStr)
{
	e_puts(shellInfo->program_name);
	e_puts(": ");
	printDecimal(shellInfo->line_number, STDERR_FILENO);
	e_puts(": ");
	e_puts(shellInfo->arguments[0]);
	e_puts(": ");
	e_puts(errorStr);
}
