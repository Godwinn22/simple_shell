#include "shell.h"

/**
 * _print - function that writes a array of chars to the stdio
 * @string: the pointer
 *
 * Return: returns the number of bytes written or,
 * On error, -1 is returned, and errno is set
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}

/**
 * _printe - function that writes an array of chars to the stderr
 * @string: the pointer
 *
 * Return: returns the number of bytes written or,
 * On error, -1 is returned, and errno is set
 */
int _printe(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * _print_error - function that writes an array of chars to the stderr
 * @data: a pointer
 * @err_code: the error code to print
 *
 * Return: returns the number of bytes written or,
 * On error, -1 is returned, and errno is set
 */
int _print_error(int err_code, data_of_program *data)
{
	char d_string[10] = {'\0'};

	long_to_string((long)data->exec_counter, d_string, 10);
	if (err_code == 2 || err_code == 3)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(d_string);
		_printe(": ");
		_printe(data->tokens[0]);
		if (err_code == 2)
			_printe(": Illegal number: ");
		else
			_printe(": can't cd to ");
		_printe(data->tokens[1]);
		_printe("\n");
	}
	else if (err_code == 127)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(d_string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": not found\n");
	}
	else if (err_code == 126)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(d_string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": Permission denied\n");
	}
	return (0);
}
