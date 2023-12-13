#include "shell.h"

/**
 * getHistoryFile - a function that retrieves the history file
 * @shellInfo: the parameter's struct
 *
 * Return: returns the allocated string containing history file
 */
char *getHistoryFile(ShellInfo *shellInfo)
{
	char *buffer, *directory;

	directory = get_environ(shellInfo, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc((strn_len(directory) +
			 strn_len(HISTORY_FILE_NAME) + 2) *
			sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	strn_cpy(buffer, directory);
	strn_cat(buffer, "/");
	strn_cat(buffer, HISTORY_FILE_NAME);
	return (buffer);
}

/**
 * writeHistory - function that creates a file, or appends to an existing file
 * @shellInfo: the parameter struct
 *
 * Return: returns 1 on success, else -1
 */
int writeHistory(ShellInfo *shellInfo)
{
	ssize_t fileDescriptor;
	char *filename = getHistoryFile(shellInfo);
	string_list *node = NULL;

	if (!filename)
		return (-1);
	fileDescriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fileDescriptor == -1)
		return (-1);
	for (node = shellInfo->history_list; node; node = node->next)
	{
		puts_fd(node->string, fileDescriptor);
		put_fd('\n', fileDescriptor);
	}
	put_fd(BUFFER_CLEAR, fileDescriptor);
	close(fileDescriptor);
	return (1);
}

/**
 * readHistory - function that reads history from file
 * @shellInfo: the parameter struct
 *
 * Return: returns the histcount on success, 0 otherwise
 */
int readHistory(ShellInfo *shellInfo)
{
	int i, last = 0, count = 0;
	ssize_t fileDescriptor, readLength, fileSize = 0;
	struct stat st;
	char *buffer = NULL, *filename = getHistoryFile(shellInfo);

	if (!filename)
		return (0);
	fileDescriptor = open(filename, O_RDONLY);
	free(filename);
	if (fileDescriptor == -1)
		return (0);
	if (!fstat(fileDescriptor, &st))
		fileSize = st.st_size;
	if (fileSize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fileSize + 1));
	if (!buffer)
		return (0);
	readLength = read(fileDescriptor, buffer, fileSize);
	buffer[fileSize] = 0;
	if (readLength <= 0)
		return (free(buffer), 0);
	close(fileDescriptor);
	i = 0;
	while (i < fileSize)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			buildHistoryList(shellInfo, buffer + last, count++);
			last = i + 1;
		}
		i++;
	}
	if (last != i)
		buildHistoryList(shellInfo, buffer + last, count++);
	free(buffer);
	shellInfo->history_line_count = count;
	while (shellInfo->history_line_count-- >= HISTORY_MAX_SIZE)
		remove_node_at_index(&(shellInfo->history_list), 0);
	renumberHistory(shellInfo);
	return (shellInfo->history_line_count);
}

/**
 * buildHistoryList - function that adds entry to a history linked list
 * @shellInfo: the structure containing potential arguments. Used to maintain
 * @buffer: the buffer
 * @count: the history count, histcount
 *
 * Return: Always 0 (success)
 */
int buildHistoryList(ShellInfo *shellInfo, char *buffer, int count)
{
	string_list *node = NULL;

	if (shellInfo->history_list)
		node = shellInfo->history_list;
	append_node(&node, buffer, count);
	if (!shellInfo->history_list)
		shellInfo->history_list = node;
	return (0);
}

/**
 * renumberHistory - function that renumbers the history
 * linked list after changes.
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *
 * Return: returns the new histcount
 */
int renumberHistory(ShellInfo *shellInfo)
{
	string_list *node;
	int index = 0;

	for (node = shellInfo->history_list; node; node = node->next)
		node->number = index++;
	return (shellInfo->history_line_count = index);
}
