#include "shell.h"

/**
 * print_alias - fuction that adds, removes or prints alias
 * @data: the struct
 * @alias: alias name to be printed
 * 
 * Return: 0 if success,
 * or others if declared in the arguments
 */
int print_alias(data_of_program *data, char *alias)
{
	int i, j, alias_len;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_len = str_length(alias);
		i = 0;
		while (data->alias_list[i])
		{
			if (!alias || (str_compare(data->alias_list[i], alias, alias_len) && data->alias_list[i][alias_len] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
			i++;
		}
	}

	return (0);
}

/**
 * get_alias - afunction that gets an alias
 * @data: the struct
 * @aliasname: the alias name
 * 
 * Return: returns 0 if sucessful
 */
char *get_alias(data_of_program *data, char *aliasname)
{
	int i, alias_len;

	if (aliasname == NULL || data->alias_list == NULL)
		return (NULL);
	alias_len = str_length(aliasname);
	i = 0;
	while (data->alias_list[i])
	{
		if (str_compare(aliasname, data->alias_list[i], alias_len) &&
		    data->alias_list[i][alias_len] == '=')
		{
			return (data->alias_list[i] + alias_len + 1);
		}
		i++;
	}
	return (NULL);
}

/**
 * set_alias - function that initializes an alias
 * @alias_str: the alias to be initialised
 * @data: the struct
 * 
 * Return: 0 if sucessful
 */
int set_alias(char *alias_str, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *tmp = NULL;

	if (alias_str == NULL || data->alias_list == NULL)
		return (1);
	for (i = 0; alias_str[i]; i++)
		if (alias_str[i] != '=')
			buffer[i] = alias_str[i];
		else
		{
			tmp = get_alias(data, alias_str + i + 1);
			break;
		}
	for (j = 0; data->alias_list[j]; j++)
		if (str_compare(buffer, data->alias_list[j], i) &&
		    data->alias_list[j][i] == '=')
		{
			free(data->alias_list[j]);
			break;
		}
	if (tmp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, tmp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else
		data->alias_list[j] = str_duplicate(alias_str);
	return (0);
}
