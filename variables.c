#include "shell.h"

/* Tests if the current character in the buffer is a chain delimiter */
int is_chain_delimiter(info_t *information, char *buffer, size_t *position)
{
	size_t j = *position;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		information->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		information->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';') /* Found the end of this command */
	{
		buffer[j] = 0; /* Replace semicolon with null */
		information->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*position = j;
	return (1);
}

/* Checks whether we should continue chaining based on the last status */
void check_chain_status(info_t *information, char *buffer, size_t *position, size_t start, size_t length)
{
	size_t j = *position;

	if (information->cmd_buf_type == CMD_AND)
	{
		if (information->status)
		{
			buffer[start] = 0;
			j = length;
		}
	}
	if (information->cmd_buf_type == CMD_OR)
	{
		if (!information->status)
		{
			buffer[start] = 0;
			j = length;
		}
	}

	*position = j;
}

/* Replaces an alias in the tokenized string */
int replace_alias_in_string(info_t *information)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_node_with_prefix(information->alias, information->argv[0], '=');
		if (!node)
			return (0);
		free(information->argv[0]);
		p = find_character(node->str, '=');
		if (!p)
			return (0);
		p = duplicate_string(p + 1);
		if (!p)
			return (0);
		information->argv[0] = p;
	}
	return (1);
}

/* Replaces variables in the tokenized string */
int replace_variables_in_string(info_t *information)
{
	int i = 0;
	list_t *node;

	for (i = 0; information->argv[i]; i++)
	{
		if (information->argv[i][0] != '$' || !information->argv[i][1])
			continue;

		if (compare_strings(information->argv[i], "$?"))
		{
			replace_string(&(information->argv[i]),
						   duplicate_string(convert_number(information->status, 10, 0)));
			continue;
		}
		if (compare_strings(information->argv[i], "$$"))
		{
			replace_string(&(information->argv[i]),
						   duplicate_string(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = find_node_with_prefix(information->env, &information->argv[i][1], '=');
		if (node)
		{
			replace_string(&(information->argv[i]),
						   duplicate_string(find_character(node->str, '=') + 1));
			continue;
		}
		replace_string(&information->argv[i], duplicate_string(""));

	}
	return (0);
}

/* Replaces a string */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
