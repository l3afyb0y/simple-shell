#ifndef CELL_H
# define CELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>

/* ANSI color codes for terminal output */
# define COLOR_RESET "\x1b[0m"
# define COLOR_BOLD "\x1b[1m"
# define COLOR_DIM "\x1b[2m"

# define BLACK "\x1b[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"

# define BRIGHT_BLACK "\x1b[90m"
# define BRIGHT_RED "\x1b[91m"
# define BRIGHT_GREEN "\x1b[92m"
# define BRIGHT_YELLOW "\x1b[93m"
# define BRIGHT_BLUE "\x1b[94m"
# define BRIGHT_MAGENTA "\x1b[95m"
# define BRIGHT_CYAN "\x1b[96m"
# define BRIGHT_WHITE "\x1b[97m"
# define RST "\033[0m"

# define p(...) printf(__VA_ARGS__)

typedef struct s_builtin
{
    const char  *name;
    int (*func)(char **);
}   t_builtin;

void    *Getcwd(char *, size_t);
void    *Malloc(size_t size);
void    *Realloc(void *ptr, size_t size);
void    printbanner(void);
char    **cell_split_line(char *line);

#endif
