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
		initializeShellInfo(shellInfo);
		if (isInteractive(shellInfo))
			_puts("$ ");
		e_putchar(BUFFER_CLEAR);
		read_status = getInputLine(shellInfo);
		if (read_status != -1)
		{
			setShellInfo(shellInfo, args);
			builtin_command_return = execute_builtin_command(shellInfo);
			if (builtin_command_return == -1)
				executeCommand(shellInfo);
		}
		else if (isInteractive(shellInfo))
			_putchar('\n');
		freeShellInfo(shellInfo, 0);
	}
	writeHistory(shellInfo);
	freeShellInfo(shellInfo, 1);
	if (!isInteractive(shellInfo) && shellInfo->last_command_status)
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
	    {"env", _env},
	    {"help", _help},
	    {"history", _History},
	    {"setenv", init_environ},
	    {"unsetenv", uninit_environ},
	    {"cd", _cd},
	    {"alias", handleAlias},
	    {NULL, NULL}};
	for (i = 0; builtin_commands[i].command_name; i++)
		if (str_cmp(shellInfo->arguments[0],
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
		if (!isDelimiter(shellInfo->input_line[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findCommandInPath(shellInfo,
				 get_environ(shellInfo, "PATH="),
				 shellInfo->arguments[0]);
	if (path)
	{
		shellInfo->command_path = path;
		executeCommand(shellInfo);
	}
	else
	{
		if ((isInteractive(shellInfo) ||
		     get_environ(shellInfo, "PATH=") || shellInfo->arguments[0][0] == '/') &&
		    isExecutable(shellInfo, shellInfo->arguments[0]))
			executeCommand(shellInfo);
		else if (*(shellInfo->input_line) != '\n')
		{
			shellInfo->last_command_status = 127;
			printError(shellInfo, "not found\n");
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
			   get_env(shellInfo)) == -1)
		{
			freeShellInfo(shellInfo, 1);
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
			shellInfo->last_command_status = WEXITSTATUS(shellInfo->last_command_status);
			if (shellInfo->last_command_status == 126)
				printError(shellInfo, "Permission denied\n");
		}
	}
}
