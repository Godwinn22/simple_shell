#include "shell.h"
/**
 * _strtok - function that separates strings with delims
 * @line: the pointer to array we receive in the getline.
 * @delim: the chars we mark off strings.
 * Return: returns a  pointer to the created token
 */
char *_strtok(char *line, char *delim)
{
	int j;
	static char *str;
	char *copy_str;

	if (line != NULL)
		str = line;
	while (*str != '\0')
	{
		j = 0;
		while (delim[j] != '\0')
		{
			if (*str == delim[j])
				break;
			j++;
		}
		if (delim[j] == '\0')
			break;
		str++;
	}
	copy_str = str;
	if (*copy_str == '\0')
		return (NULL);
	while (*str != '\0')
	{
		j = 0;
		while (delim[j] != '\0')
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (copy_str);
			}
			j++;
		}
		str++;
	}
	return (copy_str);
}

/**
 * tokenize -function that separate the string via a designed delim
 * @data: the pointer to the program's data
 *
 * Return: returns an array of the different parts of the string
 */
void tokenize(data_of_program *data)
{
	char *delim = " \t";
	int i, j, count = 2, len;

	len = str_length(data->input_line);
	if (len)
	{
		if (data->input_line[len - 1] == '\n')
			data->input_line[len - 1] = '\0';
	}
	i = 0;
	while (data->input_line[i])
	{
		j = 0;
		while (delim[j])
		{
			if (data->input_line[i] == delim[j])
				count++;
			j++;
		}
		i++;
	}

	data->tokens = malloc(count * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = str_duplicate(_strtok(data->input_line, delim));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = str_duplicate(_strtok(NULL, delim));
	}
}
