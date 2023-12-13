#include "shell.h"

/**
 * run_shell - main shell loop
 * @shellInfo: the parameter & return info struct
 * @args: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int run_shell(ShellInfo *shellInfo, char **args)
{
	ssize_t read_status = 0;
	int builtin_command_return = 0;

	while (read_status != -1 && builtin_command_return != -2)
	{
		initialize_shellInfo(shellInfo);
		if (is_interactive_mode(shellInfo))
			print_prompt("$ ");
		flush_buffer(BUFFER_CLEAR);
		read_status = get_user_input(shellInfo);
		if (read_status != -1)
		{
			set_shellInfo(shellInfo, args);
			builtin_command_return = execute_builtin_command(shellInfo);
			if (builtin_command_return == -1)
				execute_command(shellInfo);
		}
		else if (is_interactive_mode(shellInfo))
			print_newline();
		free_shellInfo(shellInfo, 0);
	}
	save_command_history(shellInfo);
	free_shellInfo(shellInfo, 1);
	if (!is_interactive_mode(shellInfo) && shellInfo->last_command_status)
		exit(shellInfo->last_command_status);
	if (builtin_command_return == -2)
	{
		if (shellInfo->exit_code == -1)
			exit(shellInfo->last_command_status);
		exit(shellInfo->exit_code);
	}
	return (builtin_command_return);
}

/**
 * execute_builtin_command - finds and executes a builtin command
 * @shellInfo: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *        0 if builtin executed successfully,
 *        1 if builtin found but not successful,
 *        -2 if builtin signals exit()
 */
int execute_builtin_command(ShellInfo *shellInfo)
{
	int i, builtin_command_return = -1;
	BuiltInCommandTable builtin_commands[] = {
	    {"exit", exitShell},
	    {"env", print_environment},
	    {"help", _help},
	    {"history", _History},
	    {"setenv", set_environment_variable},
	    {"unsetenv", unset_environment_variable},
	    {"cd", _cd},
	    {"alias", setAlias},
	    {NULL, NULL}};
	for (i = 0; builtin_commands[i].command_name; i++)
		if (compare_strings(shellInfo->arguments[0],
		builtin_commands[i].command_name) == 0)
		{
			shellInfo->line_number++;
			builtin_command_return = builtin_commands[i].execute(shellInfo);
			break;
		}
	return (builtin_command_return);
}

/**
 * execute_path - finds and executes a command in PATH
 * @shellInfo: the parameter & return info struct
 *
 * Return: void
 */
void execute_path(ShellInfo *shellInfo)
{
	char *path = NULL;
	int i, k;

	shellInfo->command_path = shellInfo->arguments[0];
	if (shellInfo->count_line_flag == 1)
	{
		shellInfo->line_number++;
		shellInfo->count_line_flag = 0;
	}
	for (i = 0, k = 0; shellInfo->input_line[i]; i++)
		if (!is_delimiter(shellInfo->input_line[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_command_path(shellInfo,
			get_environment_variable(shellInfo, "PATH="),
			shellInfo->arguments[0]);
	if (path)
	{
		shellInfo->command_path = path;
		execute_command_in_new_process(shellInfo);
	}
	else
	{
		if ((is_interactive_mode(shellInfo) || get_environment_variable
					(shellInfo, "PATH=") || shellInfo->arguments[0] == '/') &&
				is_command(shellInfo, shellInfo->arguments[0]))
			execute_command_in_new_process(shellInfo);
		else if (*(shellInfo->input_line) != '\n')
		{
			shellInfo->last_command_status = 127;
			print_error(shellInfo, "not found\n");
		}
	}
}

/**
 * executeCommand - function that creates a new process to execute a command
 * @shellInfo: the parameter & return shell info struct
 *
 * Return: void
 */
void executeCommand(ShellInfo *shellInfo)
{
	pid_t processId;

	processId = fork();
	if (processId == -1)
	{
		perror("Error in forking process:");
		return;
	}
	if (processId == 0)
	{
		if (execve(shellInfo->command_path, shellInfo->arguments,
					environment_variables) == -1)
		{
			freeshellInfo(shellInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(shellInfo->last_command_status));
		if (WIFEXITED(shellInfo->last_command_status))
		{
			shellInfo->last_command_status = WEXITSTATUS
				(shellInfo->last_command_status);
			if (shellInfo->last_command_status == 126)
				printError(shellInfo, "Permission denied\n");
		}
	}
}
