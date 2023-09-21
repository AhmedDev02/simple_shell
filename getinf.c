#include "shell.h"

// Ini information_t struct
void ini_inf(information_t *information)
{
    information->arg = NULL;
    information->argv = NULL;
    information->path = NULL;
    information->argc = 0;
}

// Set up information_t struct with arguments
void set_inf(information_t *information, char **av)
{
    int i = 0;

    information->fname = av[0];
    if (information->arg)
    {
        information->argv = strtow(information->arg, " \t");
        if (!information->argv)
        {
            information->argv = malloc(sizeof(char *) * 2);
            if (information->argv)
            {
                information->argv[0] = _strdup(information->arg);
                information->argv[1] = NULL;
            }
        }
        for (i = 0; information->argv && information->argv[i]; i++)
            ;
        information->argc = i;

        rep_ali(information);
        rep_var(information);
    }
}

// Free resources in information_t struct
void fre_inf(information_t *information, int free_all)
{
    ffr(information->argv);
    information->argv = NULL;
    information->path = NULL;
    if (free_all)
    {
        if (!information->cmd_buf)
            free(information->arg);
        if (information->env)
            free_lis(&(information->env));
        if (information->history)
            free_lis(&(information->history));
        if (information->alias)
            free_lis(&(information->alias));
        ffr(information->environ);
        information->environ = NULL;
        bfr((void **)information->cmd_buf);
        if (information->readfd > 2)
            close(information->readfd);
        _putchar(BUF_FLUSH);
    }
}
