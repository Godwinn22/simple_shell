#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - function that find a program path
 * @data: the pointer to the program's data
 * 
 * Return: returns 0 if success, errnor otherwise
 */

int find_program(data_of_program *data)
{
	int i = 0, ret_code = 0;
	char **dirs;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	dirs = tokenize_path(data);

	if (!dirs || !dirs[0])
	{
		errno = 127;
		return (127);
	}
	i = 0;
	while (dirs[i])
	{
		dirs[i] = str_concat(dirs[i], data->tokens[0]);
		ret_code = check_file(dirs[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(dirs[i]);
			free_array_of_pointers(dirs);
			return (ret_code);
		}
		i++;
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(dirs);
	return (ret_code);
}

/**
 * tokenize_path - function that tokenize the path in dirs
 * @data: the pointer to the program's data
 * Return: the array of path dirs
 */

char **tokenize_path(data_of_program *data)
{
	int i = 0;
	int count_dirs = 2;
	char **tokenss = NULL;
	char *PATH;

	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			count_dirs++;
	}

	tokenss = malloc(sizeof(char *) * count_dirs);

	i = 0;
	tokenss[i] = str_duplicate(_strtok(PATH, ":"));
	while (tokenss[i++])
	{
		tokenss[i] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokenss);
}

/**
 * check_file - function that checks if a file exists, if mnot,
 * a directory and if it has excecution permisions for permisions.
 * @full_path: the pointer to the full file name
 * 
 * Return: returns 0 on success, or errno code if it exists.
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
