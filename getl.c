#include "shell.h"

ssize_t inpu(info_t *info, char **buff, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len)
    {
        free(*buff);
        *buff = NULL;
        signal(SIGINT, sigi);
#if USE_GETLINE
        r = getline(buff, &len_p, stdin);
#else
        r = gline(info, buff, &len_p);
#endif
        if (r > 0)
        {
            if ((*buff)[r - 1] == '\n')
            {
                (*buff)[r - 1] = '\0';
                r--;
            }
            info->linecount_flag = 1;
            remv_comments(*buff);
            build_hlist(info, *buff, info->histcount++);
        }
    }
    return (r);
}

ssize_t get_(info_t *info)
{
    static char *buff;
    static size_t i, j, len;
    ssize_t r = 0;
    char **buff_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    r = inpu(info, &buff, &len);
    if (r == -1)
        return (-1);
    if (len)
    {
        j = i;
        p = buff + i;

        chck_chain(info, buff, &j, i, len);
        while (j < len)
        {
            if (is_ch(info, buff, &j))
                break;
            j++;
        }

        i = j + 1;
        if (i >= len)
        {
            i = len = 0;
            info->cmd_buf_type = CMD_NORM;
        }

        *buff_p = p;
        return (_strlen(p));
    }

    *buff_p = buff;
    return (r);
}

ssize_t rea(info_t *info, char *buff, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return (0);
    r = read(info->readfd, buff, READ_BUF_SIZE);
    if (r >= 0)
        *i = r;
    return (r);
}

int gline(info_t *info, char **ptr, size_t *length)
{
    static char buff[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = rea(info, buff, &len);
    if (r == -1 || (r == 0 && len == 0))
        return (-1);

    c = _strchr(buff + i, '\n');
    k = c ? 1 + (unsigned int)(c - buff) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p)
        return (p ? free(p), -1 : -1);

    if (s)
        _strncat(new_p, buff + i, k - i);
    else
        _strncpy(new_p, buff + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return (s);
}

void sigi(__attribute__((unused))int s_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
