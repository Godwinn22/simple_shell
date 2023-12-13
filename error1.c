#include "shell.h"

/**
 * e_puts - prints an input string to stderr
 * @strToPrint: the string to be printed
 *
 * Return: Nothing
 */
void e_puts(char *strToPrint)
{
	int i = 0;

	if (!strToPrint)
		return;
	for (; strToPrint[i] != '\0'; i++)
	{
		e_putchar(strToPrint[i]);
	}
}

/**
 * e_putchar - writes the character to stderr
 * @charToPrint: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and the errno is set appropriately.
 */
int e_putchar(char charToPrint)
{
	static int i;
	static char buffer[BUFFER_SIZE_WRITE];

	if (charToPrint == BUFFER_CLEAR || i >= BUFFER_SIZE_WRITE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (charToPrint != BUFFER_CLEAR)
		buffer[i++] = charToPrint;
	return (1);
}

/**
 * put_fd - function that writes the character to
 * given the file descriptor
 * @charToWrite: The character to write out
 * @fileDescriptor: The file descriptor to write out to
 *
 * Return: On success returns 1.
 * On error, -1 is returned, and the errno is set appropriately.
 */
int put_fd(char charToWrite, int fileDescriptor)
{
	static int i;
	static char buffer[BUFFER_SIZE_WRITE];

	if (charToWrite == BUFFER_CLEAR || i >= BUFFER_SIZE_WRITE)
	{
		write(fileDescriptor, buffer, i);
		i = 0;
	}
	if (charToWrite != BUFFER_CLEAR)
		buffer[i++] = charToWrite;
	return (1);
}

/**
 * puts_fd - writes an input string to file descriptor
 * @strToWrite: the string to be written out.
 * @fileDescriptor: the file descriptor to write out to
 *
 * Return: the number of characters written
 */
int puts_fd(char *strToWrite, int fileDescriptor)
{
	int i = 0;

	if (!strToWrite)
		return (0);
	for (; *strToWrite; i +=
			    put_fd(*strToWrite++, fileDescriptor))
		;
	return (i);
}

/**
 * err_atoi - function that converts a string to an integer
 * @strToConvert: the string to be converted
 *
 * Return: returns 0 if no numbers in string, converted number,
 * otherwise -1 on error
 */
int err_atoi(char *strToConvert)
{
	int i = 0;
	unsigned long int result = 0;

	if (*strToConvert == '+')
		strToConvert++;
	for (i = 0; strToConvert[i] != '\0'; i++)
	{
		if (strToConvert[i] >= '0' && strToConvert[i] <= '9')
		{
			result *= 10;
			result += (strToConvert[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
