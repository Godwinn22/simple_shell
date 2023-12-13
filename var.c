#include "shell.h"

/**
 * substitute_strings - function that substitutes a string
 * @old_string: the address of teh old string
 * @new_string: the new string
 *
 * Return: returns 1 if replaced,and  0 otherwise
 */
int substitute_strings(char **old_string, char *new_string)
{
	free(*old_string);
	*old_string = new_string;
	return (1);
}

/**
 * is_cmd_chain - function that test if current cmd in buffer
 * is a chain delimeter
 * @shellInfo: the parameter's struct
 * @buffer: the character buffer
 * @position: the address of the current position in buf
 *
 * Return: returns 1 if chain delimeter, 0 otherwise
 */
int is_cmd_chain(ShellInfo *shellInfo, char *buffer, size_t *position)
{
	size_t index = *position;

	switch (buffer[index])
	{
	case '|':
		if (buffer[index + 1] == '|')
		{
			buffer[index] = '\0';
			index++;
			shellInfo->command_buffer_type = COMMAND_OR;
		}
		break;

	case '&':
		if (buffer[index + 1] == '&')
		{
			buffer[index] = '\0';
			index++;
			shellInfo->command_buffer_type = COMMAND_AND;
		}
		break;

	case ';':
		buffer[index] = '\0';
		shellInfo->command_buffer_type = COMMAND_CHAIN;
		break;

	default:
		return (0);
	}

	*position = index;
	return (1);
}

/**
 * eval_chain -function that evaluates and tells if we should continue chaining
 * based on last last_command_status
 * @shellInfo: the parameter's struct
 * @buffer: the character's buffer
 * @position: the address of the current position in buffer
 * @start: the starting position in buffer
 * @length: the length of the buffer
 *
 * Return: Void
 */
void eval_chain(ShellInfo *shellInfo, char *buffer, size_t *position,
		size_t start, size_t length)
{
	size_t index = *position;

	if (shellInfo->command_buffer_type == COMMAND_AND)
	{
		if (shellInfo->last_command_status)
		{
			buffer[start] = 0;
			index = length;
		}
	}
	if (shellInfo->command_buffer_type == COMMAND_OR)
	{
		if (!shellInfo->last_command_status)
		{
			buffer[start] = 0;
			index = length;
		}
	}

	*position = index;
}

/**
 * substitute_alias - function that substitutes an
 * alias in the tokenized string
 * @shellInfo: the parameter's struct
 *
 * Return: returns 1 if replaced, and 0 otherwise
 */
int substitute_alias(ShellInfo *shellInfo)
{
	int i;
	StringNumberList *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_node_with_prefix(shellInfo->alias_list,
					     shellInfo->arguments[0], '=');
		if (!node)
			return (0);
		free(shellInfo->arguments[0]);
		p = _str_chr(node->string, '=');
		if (!p)
			return (0);
		p = strn_dup(p + 1);
		if (!p)
			return (0);
		shellInfo->arguments[0] = p;
	}
	return (1);
}

/**
 * substitute_vars -function that substitutes variables in the tokenized string
 * @shellInfo: the parameter's struct
 *
 * Return: returns 1 if replaced, and 0 otherwise
 */
int substitute_vars(ShellInfo *shellInfo)
{
	int i = 0;
	StringNumberList *node;

	while (shellInfo->arguments[i])
	{
		if (shellInfo->arguments[i][0] != '$' ||
		    !shellInfo->arguments[i][1])
			continue;

		if (str_cmp(shellInfo->arguments[i], "$?"))
		{
			substitute_strings(&(shellInfo->arguments[i]),
					   strn_dup(convertNum(shellInfo->last_command_status, 10, 0)));
			continue;
		}
		if (!_strcmp(shellInfo->arguments[i], "$$"))
		{
			substitute_strings(&(shellInfo->arguments[i]),
					   strn_dup(convertNum(getpid(), 10, 0)));
			continue;
		}
		node = find_node_with_prefix(shellInfo->environment_list,
					     &shellInfo->arguments[i][1], '=');
		if (node)
		{
			substitute_strings(&(shellInfo->arguments[i]),
					   strn_dup(_str_chr(node->string, '=') + 1));
			continue;
		}
		substitute_strings(&shellInfo->arguments[i], strn_dup(""));
		i++;
	}
	return (0);
}
