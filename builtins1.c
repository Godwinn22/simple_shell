#include "shell.h"

/**
 * builtins_list - function that searches match and execute associate builtin
 * @data: the struct
 *
 * Return: returns the result of the function executed if there is a match,
 * otherwise returns -1.
 **/
int builtins_list(data_of_program *data)
{
	int i;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	for (i = 0; options[i].builtin != NULL; i++)
	{
		if (str_compare(options[i].builtin, data->command_name, 0))
		{

			return (options[i].function(data));
		}
	}
	return (-1);
}

/**
 * builtin_env - function that shows shell running environment
 * @data: the struct
 *
 * Return: 0 if successful
 */
int builtin_env(data_of_program *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		i = 0;
		while (data->tokens[1][i])
		{
			if (data->tokens[1][i] == '=')
			{
				var_copy = str_duplicate(env_get_key(cpname, data));
				if (var_copy != NULL)
					env_set_key(cpname, data->tokens[1] + i + 1, data);
				print_environ(data);
				if (env_get_key(cpname, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					env_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
			i++;
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - function that initialises the environment variables
 * @data: the struct
 *
 * Return: Always 0 (success)
 */
int builtin_set_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_set_key(data->tokens[1], data->tokens[2], data);
	return (0);
}

/**
 * builtin_unset_env - function that uninitialises the environment variables
 * @data: the struct
 *
 * Return: Always 0 (success)
 */
int builtin_unset_env(data_of_program *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);
	return (0);
}
