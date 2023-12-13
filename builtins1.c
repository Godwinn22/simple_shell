#include "shell.h"

/**
 * exitShell - function that exits the shell
 * @shellInfo: a structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: the function exits with a given exit status
 * (0) if shellInfo.argv[0] != "exit"
 */
int exitShell(ShellInfo *shellInfo)
{
	int exitCheck;

	if (shellInfo->arguments[1])
	{
		exitCheck = err_atoi(shellInfo->arguments[1]);
		if (exitCheck == -1)
		{
			shellInfo->last_command_status = 2;
			printError(shellInfo, "Illegal number: ");
			e_puts(shellInfo->arguments[1]);
			e_putchar('\n');
			return (1);
		}
		shellInfo->exit_code = err_atoi(shellInfo->arguments[1]);
		return (-2);
	}
	shellInfo->exit_code = -1;
	return (-2);
}

/**
 * _cd - function that changes the current directory of it's process
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0 (success)
 */
int _cd(ShellInfo *shellInfo)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!shellInfo->arguments[1])
	{
		dir = get_environ(shellInfo, "HOME=");
		if (!dir)
			chdir_ret =
			    chdir((dir = get_environ(shellInfo, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_cmp(shellInfo->arguments[1], "-") == 0)
	{
		if (!get_environ(shellInfo, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_environ(shellInfo, "OLDPWD=")), _putchar('\n');
		chdir_ret =
		    chdir((dir = get_environ(shellInfo, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(shellInfo->arguments[1]);
	if (chdir_ret == -1)
	{
		printError(shellInfo, "can't cd to ");
		e_puts(shellInfo->arguments[1]), e_putchar('\n');
	}
	else
	{
		init_env(shellInfo, "OLDPWD", get_environ(shellInfo, "PWD="));
		init_env(shellInfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - function that provides help information
 * @shellInfo: a structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0 (success)
 */
int _help(ShellInfo *shellInfo)
{
	char **arg_array;

	arg_array = shellInfo->arguments;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
