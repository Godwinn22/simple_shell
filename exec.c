#include "shell.h"

/**
 * execute - function that execute a command
 * @data: the pointer to the data for the program
 * Return: returns zero, otherwise, return -1.
 */
int execute(data_of_program *data)
{
	int ret_value = 0, status;
	pid_t pidd;

	ret_value = builtins_list(data);
	if (ret_value != -1)
		return (ret_value);

	ret_value = find_program(data);
	if (ret_value)
	{
		return (ret_value);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			ret_value = execve(data->tokens[0], data->tokens, data->env);
			if (ret_value == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
