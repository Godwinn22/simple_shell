#include "shell.h"

/**
 * list_length - function that checks for the length of linked list
 * @node: pointer to first node
 *
 * Return: returns the size of list
 */
size_t list_length(const StringNumberList *node)
{
	size_t count;

	for (count = 0; node; count++)
	{
		node = node->next;
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
 * display_list - function that prints all elements of a list_t linked list
 * @node: the pointer to first node
 *
 * Return: returns the size of list
 */
size_t display_list(const StringNumberList *node)
{
	size_t count;

	for (count = 0; node; count++)
	{
		_puts(convertNum(node->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(node->string ? node->string : "(nil)");
		_puts("\n");
		node = node->next;
		count++;
	}
	return (count);
}

/**
 * find_node_with_prefix - function thar returns node
 * whose string starts with the prefix
 * @node: the pointer to list head
 * @prefix: the string to match
 * @c: the next character after prefix to match
 *
 * Return: returns the match node or null
 */
StringNumberList *find_node_with_prefix(StringNumberList *node,
					char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = startsWith(node->string, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * find_node_position - function that gets the index of a node
 * @first_node: the pointer to the list head
 * @target_node: the pointer to the node
 *
 * Return: returns the index of node or -1
 */
ssize_t find_node_position(StringNumberList *first_node,
			   StringNumberList *target_node)
{
	size_t count = 0;

	while (first_node)
	{
		if (first_node == target_node)
			return (count);
		first_node = first_node->next;
		count++;
	}
	return (-1);
}
