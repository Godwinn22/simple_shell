#include "shell.h"

/**
 * get_env - function that returns the string array copy of our environ
 * @shellInfo: the struct that is containing potential arguments.
 * Used to maintain constant function prototype.
 *
 * Return: Always 0 (success)
 */
char **get_env(ShellInfo *shellInfo)
{
	if (!shellInfo->environ || shellInfo->environment_changed_flag)
	{
		shellInfo->environ =
		    convert_list_to_strings(shellInfo->environment_list);
		shellInfo->environment_changed_flag = 0;
	}

	return (shellInfo->environ);
}

/**
 * uninit_env - function that Remove an environment variable
 * @shellInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @varName: the string environment variable property
 *
 * Return: returns 1 on delete,and 0 otherwise
 */
int uninit_env(ShellInfo *shellInfo, char *varName)
{
	string_list *node = shellInfo->environment_list;
	size_t i = 0;
	char *d;

	if (!node || !varName)
		return (0);
	while (node)
	{
		d = startsWith(node->string, varName);
		if (d && *d == '=')
		{
			shellInfo->environment_changed_flag =
			    remove_node_at_index(&(shellInfo->environment_list), i);
			i = 0;
			node = shellInfo->environment_list;
			continue;
		}
		node = node->next;
		i++;
	}
	return (shellInfo->environment_changed_flag);
}

/**
 * init_env - Initialize a new environment variable,
 *            or modify an existing one
 * @shellInfo: Structure containing potential arguments. Used to maintain
 *       constant function prototype.
 * @varName: the string environment variable property
 * @varVal: the string environment variable value
 * Return: Always 0
 */
int init_env(ShellInfo *shellInfo, char *varName, char *varVal)
{
	char *buffer = NULL;
	string_list *node;
	char *p;

	if (!varName || !varVal)
		return (0);

	buffer = malloc(strn_len(varName) + strn_len(varVal) + 2);
	if (!buffer)
		return (1);
	strn_cpy(buffer, varName);
	strn_cat(buffer, "=");
	strn_cat(buffer, varVal);
	node = shellInfo->environment_list;
	while (node)
	{
		p = startsWith(node->string, varName);
		if (p && *p == '=')
		{
			free(node->string);
			node->string = buffer;
			shellInfo->environment_changed_flag = 1;
			return (0);
		}
		node = node->next;
	}
	append_node(&(shellInfo->environment_list), buffer, 0);
	free(buffer);
	shellInfo->environment_changed_flag = 1;
	return (0);
}
