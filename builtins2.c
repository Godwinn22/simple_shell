#include "shell.h"

/**
 * builtin_exit - function that exit program with the status
 * @data: the struct
 *
 * Return: 0 if sucessful.
 */
int builtin_exit(data_of_program *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
			&& data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - function that changes the directory
 * @data: the struct
 *
 * Return: 0 if successful
 */
int builtin_cd(data_of_program *data)
{
	char *home_dir = env_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int err_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				err_code = set_work_directory(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (err_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(old_dir, 128);

		return (set_work_directory(data, home_dir));
	}
	return (0);
}

/**
 * set_work_directory - function that sets the working directory
 * @data: the struct
 * @new_dir: the new path
 *
 * Return: 0 if successful
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_help - function that shows the environment where the shell runs
 * @data: the struct
 *
 * Return: 0 if successful.
 */
int builtin_help(data_of_program *data)
{
	int i, len = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		_print(messages[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	messages[1] = HELP_EXIT_MSG;
	messages[2] = HELP_ENV_MSG;
	messages[3] = HELP_SETENV_MSG;
	messages[4] = HELP_UNSETENV_MSG;
	messages[5] = HELP_CD_MSG;
	i = 0;
	while (messages[i])
	{
		len = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], messages[i], len))
		{
			_print(messages[i] + len + 1);
			return (1);
		}
		i++;
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - function that adds, removes or prints aliases
 * @data: the struct
 *
 * Return: 0 if successful.
 */
int builtin_alias(data_of_program *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));
	while (data->tokens[++i])
	{
		if (count_characters(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			print_alias(data, data->tokens[i]);
	}

	return (0);
}
