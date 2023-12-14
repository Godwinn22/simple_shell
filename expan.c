#include "shell.h"

/**
 * expand_variables - function that expand the variables
 * @data: the program's data pointer
 *
 * Return: returns nothing, but sets the error.
 */
void expand_variables(data_of_program *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	int i = 0;
	while (line[i])
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			j = 1;
			while (line[i + j] && line[i + j] != ' ')
				expansion[j - 1] = line[i + j], j++;
			temp = env_get_key(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	i++;
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - expand aliases
 * @data: the program's data pointer
 *
 * Return: nothing, but sets error.
 */
void expand_alias(data_of_program *data)
{
	int i, j, expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';
		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			line[i] = '\0';
			buffer_add(line, temp);
			line[str_len(line)] = '\0';
			buffer_add(line, expansion);
			expanded = 1;
		}
		break;
	}
	if (expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - function that append string at end of the buffer
 * @buffer: the buffer to be filled
 * @str_to_add: the string to be copied in the buffer
 * Return: returns nothing, but sets errno.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int len, i= 0;

	len = str_len(buffer);
	while (str_to_add[i])
	{
		buffer[len + i] = str_to_add[i];
		i++;
	}
	buffer[len + i] = '\0';
	return (len + i);
}
