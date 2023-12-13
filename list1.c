#include "shell.h"

/**
 * prepend_node - function that appends a node at the start of the list
 * @list_head: address of pointer to head node
 * @string: the string field of node
 * @number: the node number used by history
 *
 * Return: returns the size of the list
 */
string_list *prepend_node(string_list **list_head,
			       const char *string, int number)
{
	string_list *new_node;

	if (!list_head)
		return (NULL);
	new_node = malloc(sizeof(string_list));
	if (!new_node)
		return (NULL);
	mem_set((void *)new_node, 0, sizeof(string_list));
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
string_list *append_node(string_list **list_head,
			      const char *string, int number)
{
	string_list *new_node, *temp_node;

	if (!list_head)
		return (NULL);

	temp_node = *list_head;
	new_node = malloc(sizeof(string_list));
	if (!new_node)
		return (NULL);
	mem_set((void *)new_node, 0, sizeof(string_list));
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
 * element of a string_list linked list
 * @node: the pointer to first node
 *
 * Return: returns the size count of list
 */
size_t display_list_data(const string_list *node)
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
char **convert_list_to_strings(string_list *first_node)
{
	string_list *current_node = first_node;
	size_t i = list_length(first_node), j;
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
		string = malloc(strn_len(current_node->string) + 1);
		if (!string)
		{
			for (j = 0; j < i; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		string = strn_cpy(string, current_node->string);
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
void free_list(string_list **list_head_ptr)
{
	string_list *current_node, *next_node, *list_head;

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
