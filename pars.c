#include "shell.h"

#define MY_NULL ((void *)0)

// Check if a file is an executable command
int is_command(info_t *information, char *file_path)
{
    struct stat file_stat;

    (void)information;

    if (!file_path || stat(file_path, &file_stat))
        return (0);

    if (file_stat.st_mode & S_IFREG)
        return (1);

    return (0);
}

// Duplicate characters in a string
char *copy_chars(char *source_str, int start_index, int stop_index)
{
    static char buffer[1024];
    int i = 0, k = 0;

    for (k = 0, i = start_index; i < stop_index; i++)
        if (source_str[i] != ':')
            buffer[k++] = source_str[i];

    buffer[k] = 0;
    return (buffer);
}

// Find a command in the PATH string
char *find_command(info_t *information, char *path_string, char *command)
{
    int i = 0, current_position = 0;
    char *result_path;

    if (!path_string)
        return (MY_NULL);

    if ((_strlen(command) > 2) && starts_with(command, "./"))
    {
        if (is_command(information, command))
            return (command);
    }

    while (1)
    {
        if (!path_string[i] || path_string[i] == ':')
        {
            result_path = copy_chars(path_string, current_position, i);
            if (!*result_path)
                _strcat(result_path, command);
            else
            {
                _strcat(result_path, "/");
                _strcat(result_path, command);
            }

            if (is_command(information, result_path))
                return (result_path);

            if (!path_string[i])
                break;

            current_position = i;
        }

        i++;
    }

    return (MY_NULL);
}
