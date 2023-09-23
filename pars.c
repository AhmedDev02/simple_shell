#include "shell.h"

/**
 * is_cmd_info - Determines if a file is an executable command.
 * @_info: The info struct.
 * @_path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd_info(info_t *_info, char *_path)
{
    struct stat st;

    (void)_info;
    if (!_path || stat(_path, &st))
        return (0);

    if (st.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}

/**
 * dup_chars_info - Duplicates characters.
 * @_pathstr: The PATH string.
 * @_start: Starting index.
 * @_stop: Stopping index.
 *
 * Return: Pointer to new buffer.
 */
char *dup_chars_info(char *_pathstr, int _start, int _stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = _start; i < _stop; i++)
        if (_pathstr[i] != ':')
            buf[k++] = _pathstr[i];
    buf[k] = 0;
    return (buf);
}

/**
 * find_path_info - Finds this cmd in the PATH string.
 * @_info: The info struct.
 * @_pathstr: The PATH string.
 * @_cmd: The cmd to find.
 *
 * Return: Full path of cmd if found or NULL.
 */
char *find_path_info(info_t *_info, char *_pathstr, char *_cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!_pathstr)
        return (NULL);
    if ((_strlen(_cmd) > 2) && starts_with(_cmd, "./"))
    {
        if (is_cmd_info(_info, _cmd))
            return (_cmd);
    }
    while (1)
    {
        if (!_pathstr[i] || _pathstr[i] == ':')
        {
            path = dup_chars_info(_pathstr, curr_pos, i);
            if (!*path)
                _strcat(path, _cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, _cmd);
            }
            if (is_cmd_info(_info, path))
                return (path);
            if (!_pathstr[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return (NULL);
}
