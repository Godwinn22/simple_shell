#include "shell.h"

/**
 * prepend_node - function that appends a node at the start of the list
 * @list_head: address of pointer to head node
 * @string: the string field of node
 * @number: the node number used by history
 *
 * Return: returns the size of the list
 */
StringNumberList *prepend_node(StringNumberList **list_head,
			       const char *string, int number)
{
	StringNumberList *new_node;

	if (!list_head)
		return (NULL);
	new_node = malloc(sizeof(StringNumberList));
	if (!new_node)
		return (NULL);
	mem_set((void *)new_node, 0, sizeof(StringNumberList));
	new_node->number = number;
	if (string)
	{
		new_node->string = strn_dup(string);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *list_head;
	*list_head = new_node;
	return (new_node);
}

/**
 * append_node - function that appends a node to the end of the list
 * @list_head: the address of pointer to head node
 * @string: the str field of node
 * @number: the node number that is used by history
 *
 * Return: returns the size of the list
 */
StringNumberList *append_node(StringNumberList **list_head,
			      const char *string, int number)
{
	StringNumberList *new_node, *temp_node;

	if (!list_head)
		return (NULL);

	temp_node = *list_head;
	new_node = malloc(sizeof(StringNumberList));
	if (!new_node)
		return (NULL);
	mem_set((void *)new_node, 0, sizeof(StringNumberList));
	new_node->number = number;
	if (string)
	{
		new_node->string = strn_dup(string);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (temp_node)
	{
		while (temp_node->next)
			temp_node = temp_node->next;
		temp_node->next = new_node;
	}
	else
		*list_head = new_node;
	return (new_node);
}

/**
 * display_list_data - function that  prints only the str
 * element of a StringNumberList linked list
 * @node: the pointer to first node
 *
 * Return: returns the size count of list
 */
size_t display_list_data(const StringNumberList *node)
{
	size_t count = 0;

	while (node)
	{
		_puts(node->string ? node->string : "(nil)");
		_puts("\n");
		node = node->next;
		count++;
	}
	return (count);
}

/**
 * convert_list_to_strings - returns an array of strings of the list->string
 * @first_node: the pointer to first node
 *
 * Return: returns array of strings
 */
char **convert_list_to_strings(StringNumberList *first_node)
{
	StringNumberList *current_node = first_node;
	size_t i = calculate_list_length(first_node), j;
	char **str_array;
	char *string;

	if (!first_node || !i)
		return (NULL);
	str_array = malloc(sizeof(char *) * (i + 1));
	if (!str_array)
		return (NULL);
	i = 0;
	while (current_node)
	{
		string = malloc(_strlen(current_node->string) + 1);
		if (!string)
		{
			for (j = 0; j < i; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		string = _strcpy(string, current_node->string);
		str_array[i] = string;
		current_node = current_node->next;
		i++;
	}
	str_array[i] = NULL;
	return (str_array);
}

/**
 * free_list - a function that frees all the nodes in a list
 * @list_head_ptr: the address of the pointer to head node
 *
 * Return: void
 */
void free_list(StringNumberList **list_head_ptr)
{
	StringNumberList *current_node, *next_node, *list_head;

	if (!list_head_ptr || !*list_head_ptr)
		return;
	list_head = *list_head_ptr;
	current_node = list_head;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->string);
		free(current_node);
		current_node = next_node;
	}
	*list_head_ptr = NULL;
}
