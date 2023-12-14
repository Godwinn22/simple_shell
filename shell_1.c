#include "shell.h"

/**
 * main - function that initializes the variables of the program
 * @argc: the number of values received from the command line
 * @argv: the values received from the command line
 * @env: the number of values received from the command line
 *
 * Return: retuirns zero on success.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	initialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		/* We are in the terminal, interactive mode */
		errno = 2; /* ??????? */
		prompt = PROMPT_MSG;
	}

	errno = 0;
	sisifo(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - function that print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is sent to the program
 * @UNUSED: option of the prototype
 *
 * Return: void
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initialize_data - function that initializes the
 * struct with the info of the program
 * @data: the pointer to the structure of data
 * @argv: the array of arguments passed to the program execution
 * @env: the environ passed to the program execution
 * @argc: the number of values received from the command line
 *
 * Return: void
 */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;
	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i <= 19; i++)
	{
		data->alias_list[i] = NULL;
	}
}

/**
 * sisifo - function that runs an infinite loop to show the prompt always
 * @prompt: the prompt to be printed
 * @data: the prompt's loop
 *
 * Return: void
 */
void sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	for (; ++(data->exec_counter);)
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno); /* if EOF is the first Char of string, exit */
		}

		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);

			if (data->tokens[0])
			{
				/* if text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}

			free_recurrent_data(data);
		}
	}
}
