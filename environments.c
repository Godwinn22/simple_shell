#include "shell.h"

/**
 * env_get_key - function that gets the value of an environment variable
 * @key: the environment variable
 * @data: the struct
 *
 * Return: retruns a pointer to the value of the variable
 */
char *env_get_key(char *key, data_of_program *data)
{
	int i, key_len = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);
	key_len = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_len) &&
		    data->env[i][key_len] == '=')
		{
			return (data->env[i] + key_len + 1);
		}
	}
	return (NULL);
}

/**
 * env_set_key - function that overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: the variable name
 * @value: new value
 * @data: the struct
 *
 * Return: returns 1 if the parameters are NULL,
 * 2 if there is an erroror
 * 0 if sucess.
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int i, key_len = 0, new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);
	key_len = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_len) &&
		    data->env[i][key_len] == '=')
		{
			new_key = 0;
			free(data->env[i]);
			break;
		}
	}
	data->env[i] = str_concat(str_duplicate(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (new_key)
	{
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - function that removes a key from the environment
 * @key: the key to remove
 * @data: the sruct
 *
 * Return: returns 1 if the key was removed,
 * 0 if the key does not exist;
 */
int env_remove_key(char *key, data_of_program *data)
{
	int i, key_len = 0;

	if (key == NULL || data->env == NULL)
		return (0);
	key_len = str_length(key);
	i = 0;
	while (data->env[i])
	{
		if (str_compare(key, data->env[i], key_len) &&
		    data->env[i][key_len] == '=')
		{
			free(data->env[i]);
			i++;
			while (data->env[i])
			{
				data->env[i - 1] = data->env[i];
				i++;
			}
			data->env[i - 1] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * print_environ - function that prints the current environ
 * @data: the struct
 *
 * Return: void
 */
void print_environ(data_of_program *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
