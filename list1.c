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
 * remove_node_at_index - function that removes a node at given position
 * @list_head: the address of pointer to first node
 * @position: the beginning of node to delete
 *
 * Return: returns 1 on success, 0 on failure
 */
int remove_node_at_index(StringNumberList **list_head, unsigned int position)
{
	StringNumberList *current_node, *prev_node;
	unsigned int count = 0;

	if (!list_head || !*list_head)
		return (0);

	if (!position)
	{
		current_node = *list_head;
		*list_head = (*list_head)->next;
		free(current_node->string);
		free(current_node);
		return (1);
	}
	current_node = *list_head;
	for (; current_node; count++)
	{
		if (count == position)
		{
			prev_node->next = current_node->next;
			free(current_node->string);
			free(current_node);
			return (1);
		}
		prev_node = current_node;
		current_node = current_node->next;
	}
	return (0);
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
