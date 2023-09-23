#include "shell.h"

/**
 * get_history_file_info - Gets the history file for the provided info.
 * @info: The parameter struct.
 *
 * Return: Allocated string containing the history file.
 */
char *get_history_file_info(info_t *info)
{
	char *buf, *dir;

	dir = _getenv_info(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen_info(dir) + _strlen_info(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy_info(buf, dir);
	_strcat_info(buf, "/");
	_strcat_info(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history_info - Creates a file or appends to an existing file for the provided info.
 * @info: The parameter struct.
 *
 * Return: 1 on success, else -1.
 */
int write_history_info(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file_info(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd_info(node->str, fd);
		_putfd_info('\n', fd);
	}
	_putfd_info(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history_info - Reads history from a file for the provided info.
 * @info: The parameter struct.
 *
 * Return: Histcount on success, 0 otherwise.
 */
int read_history_info(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file_info(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list_info(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list_info(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index_info(&(info->history), 0);
	renumber_history_info(info);
	return (info->histcount);
}

/**
 * build_history_list_info - Adds an entry to a history linked list for the provided info.
 * @info: The parameter struct. Used to maintain history.
 * @buf: The buffer containing the history entry.
 * @linecount: The history linecount.
 *
 * Return: Always 0.
 */
int build_history_list_info(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end_info(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history_info - Renumbers the history linked list after changes for the provided info.
 * @info: The parameter struct. Used to maintain history.
 *
 * Return: The new histcount.
 */
int renumber_history_info(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
