#include "shell.h"

/**
 * bufferChainedCommands - function that buffers chained commands
 * @shellInfo: the parameter struct
 * @cmdBuf: the address of buffer
 * @bufLength: the address of len var
 *
 * Return: returns the bytes read
 */
ssize_t bufferChainedCommands(ShellInfo *shellInfo,
			      char **cmdBuf, size_t *bufLength)
{
	ssize_t bytesRead = 0;
	size_t len_d = 0;

	if (!*bufLength)
	{
		free(*cmdBuf);
		*cmdBuf = NULL;
		signal(SIGINT, blockCtrlC);
#if ENABLE_GETLINE
		bytesRead = getline(cmdBuf, &len_d, stdin);
#else
		bytesRead = getNextLine(shellInfo, cmdBuf, &len_d);
#endif
		if (bytesRead > 0)
		{
			if ((*cmdBuf)[bytesRead - 1] == '\n')
			{
				(*cmdBuf)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			shellInfo->count_line_flag = 1;
			stripComments(*cmdBuf);
			buildHistoryList(shellInfo, *cmdBuf, shellInfo->history_line_count++);
			{
				*bufLength = bytesRead;
				shellInfo->command_buffer = cmdBuf;
			}
		}
	}
	return (bytesRead);
}

/**
 * getInputLine - function that gets a line minus the newline
 * @shellInfo: the parameter's struct
 *
 * Return: return bytes read
 */
ssize_t getInputLine(ShellInfo *shellInfo)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t bytesRead = 0;
	char **buf_p = &(shellInfo->input_line), *p;

	_putchar(BUFFER_CLEAR);
	bytesRead = bufferChainedCommands(shellInfo, &buf, &len);
	if (bytesRead == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		eval_chain(shellInfo, buf, &j, i, len);
		while (j < len)
		{
			if (is_cmd_chain(shellInfo, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			shellInfo->command_buffer_type = COMMAND_EXECUTE;
		}

		*buf_p = p;
		return (strn_len(p));
	}

	*buf_p = buf;
	return (bytesRead);
}

/**
 * readBuffer - function that reads a buffer
 * @shellInfo: the  parameter's struct
 * @buffer: the buffer
 * @size: the buffer size
 *
 * Return: returns the byteRead
 */
ssize_t readBuffer(ShellInfo *shellInfo, char *buffer, size_t *size)
{
	ssize_t bytesRead = 0;

	if (*size)
		return (0);
	bytesRead = read(shellInfo->input_file_descriptor, buffer, BUFFER_SIZE_READ);
	if (bytesRead >= 0)
		*size = bytesRead;
	return (bytesRead);
}

/**
 * getNextLine - function that gets the next line of input from STDIN
 * @shellInfo: the parameter's struct
 * @bufferPtr: the address of pointer to buffer, preallocated or NULL
 * @bufLength: the size of preallocated bufferPtr, buffer if not NULL
 *
 * Return: returns s
 */
int getNextLine(ShellInfo *shellInfo, char **bufferPtr, size_t *bufLength)
{
	static char buffer[BUFFER_SIZE_READ];
	static size_t i, len;
	size_t k;
	ssize_t bytesRead = 0, s = 0;
	char *d = NULL, *new_d = NULL, *c;

	d = *bufferPtr;
	if (d && bufLength)
		s = *bufLength;
	if (i == len)
		i = len = 0;

	bytesRead = readBuffer(shellInfo, buffer, &len);
	if (bytesRead == -1 || (bytesRead == 0 && len == 0))
		return (-1);

	c = _str_chr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_d = _realloc(d, s, s ? s + k : k + 1);
	if (!new_d)
		return (d ? free(d), -1 : -1);

	if (s)
		_strn_cat(new_d, buffer + i, k - i);
	else
		_strn_cpy(new_d, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	d = new_d;

	if (bufLength)
		*bufLength = s;
	*bufferPtr = d;
	return (s);
}

/**
 * blockCtrlC - a function that blocks the command ctrl-C
 * @signalNumber: the signal number
 *
 * Return: (void)
 */
void blockCtrlC(__attribute__((unused)) int signalNumber)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_CLEAR);
}

