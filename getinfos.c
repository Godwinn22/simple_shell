#include "shell.h"

/**
 * free_recurrent_data - function that frees the fields needed each loop
 * @data: the struct
 *
 * Return: void
 */
void free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - function that free all field of the data
 * @data: the struct
 *
 * Return: void
 */
void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - function that frees each pointer
 * of an array of pointers and the array too
 * @array: the pointers array
 *
 * Return: void
 */
void free_array_of_pointers(char **array)
{
	int i = 0;

	if (array != NULL)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
		array = NULL;
	}
}
