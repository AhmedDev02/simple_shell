#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh_info(info_t *, char **);
int find_builtin_info(info_t *);
void find_cmd_info(info_t *);
void fork_cmd_info(info_t *);

/* toem_parser.c */
int is_cmd_info(info_t *, char *);
char *dup_chars_info(char *, int, int);
char *find_path_info(info_t *, char *, char *);

/* loophsh.c */
int loophsh_info(char **);

/* toem_errors.c */
void _eputs_info(char *);
int _eputchar_info(char);
int _putfd_info(char c, int fd);
int _putsfd_info(char *str, int fd);

/* toem_string.c */
int _strlen_info(char *);
int _strcmp_info(char *, char *);
char *starts_with_info(const char *, const char *);
char *_strcat_info(char *, char *);

/* toem_string1.c */
char *_strcpy_info(char *, char *);
char *_strdup_info(const char *);
void _puts_info(char *);
int _putchar_info(char);

/* toem_exits.c */
char *_strncat_info(char *, char *, int);
char *_strncat_info(char *, char *, int);
char *_strchr_info(char *, char);

/* toem_tokenizer.c */
char **strtow_info(char *, char *);
char **strtow2_info(char *, char);

/* toem_realloc.c */
char *_memset_info(char *, char, unsigned int);
void ffree_info(char **);
void *_realloc_info(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree_info(void **);

/* toem_atoi.c */
int interactive_info(info_t *);
int is_delim_character_string(char, char *);
int _isalpha_input(int);
int _atoi_string(char *);

/* toem_errors1.c */
int _erratoi_info(char *);
void print_error_info(info_t *, char *);
int  print_d_info(int, int);
char *convert_number_info(long int, int, int);
void remove_comments_info(char *);

/* toem_builtin.c */
int _myexit_info(info_t *);
int _mycd_info(info_t *);
int _myhelp_info(info_t *);

/* toem_builtin1.c */
int _myhistory_info(info_t *);
int _myalias_info(info_t *);

/*toem_getline.c */
ssize_t get_input_info(info_t *);
int _getline_info(info_t *, char **, size_t *);
void sigintHandler_info(int);

/* toem_getinfo.c */
void clear_info_info(info_t *);
void set_info_info(info_t *, char **);
void free_info_info(info_t *, int);

/* toem_environ.c */
char *_getenv_info_info(info_t *, const char *);
int _myenv_info_info(info_t *);
int _mysetenv_info_info(info_t *);
int _myunsetenv_info_info(info_t *);
int populate_env_list_info_info(info_t *);

/* toem_getenv.c */
char **get_environ_info(info_t *);
int _unsetenv_info(info_t *, char *);
int _setenv_info(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file_info(info_t *info);
int write_history_info(info_t *info);
int read_history_info(info_t *info);
int build_history_list_info(info_t *info, char *buf, int linecount);
int renumber_history_info(info_t *info);

/* toem_lists.c */
list_t *add_node_info(list_t **, const char *, int);
list_t *add_node_end_info(list_t **, const char *, int);
size_t print_list_str_info(const list_t *);
int delete_node_at_index_info(list_t **, unsigned int);
void free_list_info(list_t **);

/* toem_lists1.c */
size_t list_len_info(const list_t *);
char **list_to_strings_info(list_t *);
size_t print_list_info(const list_t *);
list_t *node_starts_with_info(list_t *, char *, char);
ssize_t get_node_index_info(list_t *, list_t *);

/* toem_vars.c */
int is_chain_info(info_t *, char *, size_t *);
void check_chain_info(info_t *, char *, size_t *, size_t, size_t);
int replace_alias_info(info_t *);
int replace_vars_info(info_t *);
int replace_string_info(char **, char *);

#endif
