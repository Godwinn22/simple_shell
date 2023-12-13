#include "shell.h"

/**
 * _History - function that displays the history list, one command by line,
 * preceded with line numbers, starting at 0.
 * @shellInfo: a structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0 (success)
 */
int _History(ShellInfo *shellInfo)
{
	display_list(shellInfo->history_list);
	return (0);
}

/**
 * unsetAlias - function that unsets alias to string
 * @shellInfo: the parameter's struct
 * @aliasName: the string's alias
 *
 * Return: Always 0 (success), but 1 on error
 */
int unsetAlias(ShellInfo *shellInfo, char *aliasName)
{
	char *d, s;
	int ret;

	d = _str_chr(aliasName, '=');
	if (!d)
		return (1);
	s = *d;
	*d = 0;
	ret = remove_node_at_index(&(shellInfo->alias_list),
				   find_node_position(shellInfo->alias_list,
						  find_node_with_prefix(shellInfo->alias_list, aliasName, -1)));
	*d = s;
	return (ret);
}

/**
 * setAlias - function that sets alias to string
 * @shellInfo: the parameter's struct
 * @aliasName: the string's alias
 *
 * Return: Always 0 (success), but 1 on error
 */
int setAlias(ShellInfo *shellInfo, char *aliasName)
{
	char *d;

	d = _str_chr(aliasName, '=');
	if (!d)
		return (1);
	if (!*++d)
		return (unsetAlias(shellInfo, aliasName));

	unsetAlias(shellInfo, aliasName);
	return (append_node(&(shellInfo->alias_list), aliasName, 0) == NULL);
}

/**
 * printAlias - a function that prints an alias string
 * @aliasNode: the alias's node
 *
 * Return: Always 0 (success), but 1 on error
 */
int printAlias(StringNumberList *aliasNode)
{
	char *d = NULL, *a = NULL;

	if (aliasNode)
	{
		d = _str_chr(aliasNode->string, '=');
		for (a = aliasNode->string; a <= d; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(d + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * handleAlias - function that mimics the alias builtin (man alias)
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int handleAlias(ShellInfo *shellInfo)
{
	int i = 0;
	char *p = NULL;
	StringNumberList *node = NULL;

	if (shellInfo->argument_count == 1)
	{
		node = shellInfo->alias_list;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; shellInfo->arguments[i]; i++)
	{
		p = _str_chr(shellInfo->arguments[i], '=');
		if (p)
			setAlias(shellInfo, shellInfo->arguments[i]);
		else
			printAlias(find_node_with_prefix(shellInfo->alias_list,
						shellInfo->arguments[i], '='));
	}

	return (0);
}
