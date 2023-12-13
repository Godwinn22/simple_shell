#include "shell.h"

/**
 * get_environ - function that gets the value of an environment variable
 * @shellInfo: the structure containing potential arguments. Used to maintain
 * @varName: the environment variable's name
 *
 * Return: returns NULL
 */
char *get_environ(ShellInfo *shellInfo, const char *varName)
{
	string_list *node = shellInfo->environment_list;
	char *d;

	while (node)
	{
		d = startsWith(node->string, varName);
		if (d && *d)
			return (d);
		node = node->next;
	}
	return (NULL);
}

/**
 * _env - function that prints the current environment
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0 (success)
 */
int _env(ShellInfo *shellInfo)
{
	display_list_data(shellInfo->environment_list);
	return (0);
}

/**
 * init_environ - function that Initialize a new environment
 * variable, or modify an existing one
 * @shellInfo: the structure containing potential arguments.
 * Used to maintain constant function prototype.
 *
 * Return: Always 0 (success)
 */
int init_environ(ShellInfo *shellInfo)
{
	if (shellInfo->argument_count != 3)
	{
		e_puts("Incorrect number of arguments\n");
		return (1);
	}
	if (init_env(shellInfo, shellInfo->arguments[1], shellInfo->arguments[2]))
		return (0);
	return (1);
}

/**
 * uninit_environ - function that removes an environment variable
 * @shellInfo: the structure containing potential arguments. Used to
 * maintain constant function prototype.
 *
 * Return: Always 0 (success)
 */
int uninit_environ(ShellInfo *shellInfo)
{
	int i;

	if (shellInfo->argument_count == 1)
	{
		e_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 0; i < shellInfo->argument_count; i++)
		uninit_env(shellInfo, shellInfo->arguments[i]);

	return (0);
}

/**
 * populateEnvList -a function that populates environment linked list
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0 (success)
 */
int populateEnvList(ShellInfo *shellInfo)
{
	string_list *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		append_node(&node, environ[i], 0);
	shellInfo->environment_list = node;
	return (0);
}
