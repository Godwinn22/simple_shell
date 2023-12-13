#include "shell.h"

/**
 * initializeShellInfo - function that sets up the ShellInfo struct
 * @shellInfo: the struct address to be initialised
 *
 * Return: void
 */
void initializeShellInfo(ShellInfo *shellInfo)
{
	shellInfo->input_line = NULL;
	shellInfo->arguments = NULL;
	shellInfo->command_path = NULL;
	shellInfo->argument_count = 0;
}

/**
 * setShellInfo - a function that sets the ShellInfo struct
 * @shellInfo: the struct address to be set
 * @argVector: the argument vector
 */
void setShellInfo(ShellInfo *shellInfo, char **argVector)
{
	int i = 0;

	shellInfo->program_name = argVector[0];
	if (shellInfo->input_line)
	{
		shellInfo->arguments = _strtow(shellInfo->input_line, " \t");
		if (!shellInfo->arguments)
		{

			shellInfo->arguments = malloc(sizeof(char *) * 2);
			if (shellInfo->arguments)
			{
				shellInfo->arguments[0] = strn_dup(shellInfo->input_line);
				shellInfo->arguments[1] = NULL;
			}
		}
		for (i = 0; shellInfo->arguments && shellInfo->arguments[i]; i++)
			;
		shellInfo->argument_count = i;

		substitute_alias(shellInfo);
		substitute_vars(shellInfo);
	}
}

/**
 * freeShellInfo - a function that frees ShellInfo struct fields
 * @shellInfo: the struct address to be free
 * @freeall: for freeing all fields
 */
void freeShellInfo(ShellInfo *shellInfo, int freeall)
{
	freeStrs(shellInfo->arguments);
	shellInfo->arguments = NULL;
	shellInfo->command_path = NULL;
	if (freeall)
	{
		if (!shellInfo->command_buffer)
			free(shellInfo->input_line);
		if (shellInfo->environment_list)
			free_list(&(shellInfo->environment_list));
		if (shellInfo->history_list)
			free_list(&(shellInfo->history_list));
		if (shellInfo->alias_list)
			free_list(&(shellInfo->alias_list));
		freeStrs(shellInfo->modified_environment);
		shellInfo->modified_environment = NULL;
		freeptr((void **)shellInfo->command_buffer);
		if (shellInfo->input_file_descriptor > 2)
			close(shellInfo->input_file_descriptor);
		_putchar(BUFFER_CLEAR);
	}
}
