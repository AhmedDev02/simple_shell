#include "shell.h"

// Get the history file
char *_get_history_file(information_t *information)
{
    char *buf, *dir;

    dir = _getenv(information, "HOME=");
    if (!dir)
        return (NULL);
    buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
    if (!buf)
        return (NULL);
    buf[0] = 0;
    _strcpy(buf, dir);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);
    return (buf);
}

// Write history to a file
int _writ_history(information_t *information)
{
    ssize_t fd;
    char *filename = _get_history_file(information);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return (-1);
    for (node = information->history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }
    _putfd(BUF_FLUSH, fd);
    close(fd);
    return (1);
}

// Read history from a file
int _read_history(information_t *information)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = _get_history_file(information);

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
            _build_history_list(information, buf + last, linecount++);
            last = i + 1;
        }
    if (last != i)
        _build_history_list(information, buf + last, linecount++);
    free(buf);
    information->histcount = linecount;
    while (information->histcount-- >= HIST_MAX)
        _delete_node_at_index(&(information->history), 0);
    _renumber_history(information);
    return (information->histcount);
}

// Build history linked list
int _build_history_list(information_t *information, char *buf, int linecount)
{
    list_t *node = NULL;

    if (information->history)
        node = information->history;
    _add_node_end(&node, buf, linecount);

    if (!information->history)
        information->history = node;
    return (0);
}

// Renumber the history linked list
int _renumber_history(information_t *information)
{
    list_t *node = information->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }
    return (information->histcount = i);
}
