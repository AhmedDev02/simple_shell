#include "shell.h"

/**
 * list_len_info - Determines the length of the linked list for the provided info.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t list_len_info(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings_info - Returns an array of strings of the list->str for the provided info.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **list_to_strings_info(list_t *head)
{
	list_t *node = head;
	size_t i = list_len_info(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen_info(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy_info(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list_info - Prints all elements of a list_t linked list for the provided info.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list_info(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts_info(convert_number_info(h->num, 10, 0));
		_putchar_info(':');
		_putchar_info(' ');
		_puts_info(h->str ? h->str : "(nil)");
		_puts_info("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with_info - Returns the node whose string starts with prefix for the provided info.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after prefix to match.
 *
 * Return: The matching node or NULL.
 */
list_t *node_starts_with_info(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with_info(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index_info - Gets the index of a node for the provided info.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: The index of the node or -1.
 */
ssize_t get_node_index_info(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
