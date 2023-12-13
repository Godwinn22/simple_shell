#include "shell.h"

/**
 * isExecutable - function that checks if a file is an executable command
 * @shellInfo: the shell info's struct
 * @filePath: the file's path
 *
 * Return: returns 1 if true, 0 otherwise
 */
int isExecutable(ShellInfo *shellInfo, char *filePath)
{
	struct stat fileStat;

	(void)shellInfo;
	if (!filePath || stat(filePath, &fileStat))
		return (0);

	if (fileStat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * *duplicateCharacters - function that duplicates the characters
 * @inputStr: the input string
 * @startIndex: the starting index
 * @endIndex: the stopping index
 *
 * Return: returns the pointer to the new buffer
 */
char *duplicateCharacters(char *inputStr, int startIndex, int endIndex)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = startIndex; i < endIndex; i++)
		if (inputStr[i] != ':')
			buffer[k++] = inputStr[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * findCommandInPath - finds this command in the PATH string
 * @shellInfo: the shell info struct
 * @pathStr: the string's PATH
 * @command: the command we want to find
 *
 * Return: returns the full path of command if found or if NULL
 */
char *findCommandInPath(ShellInfo *shellInfo, char *pathStr, char *command)
{
	int i = 0, current_pos = 0;
	char *path;

	if (!pathStr)
		return (NULL);
	if ((strn_len(command) > 2) && startsWith(command, "./"))
	{
		if (isExecutable(shellInfo, command))
			return (command);
	}
	for (; 1; i++)
	{
		if (!pathStr[i] || pathStr[i] == ':')
		{
			path = duplicateCharacters(pathStr, current_pos, i);
			if (!*path)
				strn_cat(path, command);
			else
			{
				strn_cat(path, "/");
				strn_cat(path, command);
			}
			if (isExecutable(shellInfo, path))
				return (path);
			if (!pathStr[i])
				break;
			current_pos = i;
		}
	}
	return (NULL);
}
