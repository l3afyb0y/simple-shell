#include "cell.h"
#include <string.h>

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"

/*
 * Split input line into tokens.
 * Returns a NULL-terminated array of strings owned by the caller.
 */
char **cell_split_line(char *line)
{
    int bufsize = TOKEN_BUFSIZE;
    int position = 0;
    char **tokens = Malloc(sizeof(char *) * bufsize);
    char *token;

    token = strtok(line, TOKEN_DELIM);
    while (token != NULL)
    {
        tokens[position++] = token;
        if (position >= bufsize)
        {
            bufsize += TOKEN_BUFSIZE;
            tokens = Realloc(tokens, sizeof(char *) * bufsize);
        }
        token = strtok(NULL, TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
