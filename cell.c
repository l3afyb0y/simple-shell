#include "cell.h"

static int  cell_cd(char **args);
static int  cell_help(char **args);
static int  cell_env(char **args);
static int  cell_exit(char **args);
static int  cell_launch(char **args);
static int  cell_execute(char **args);
static char *cell_read_line(void);

extern char **environ;

static const t_builtin g_builtins[] = {
    {"cd", cell_cd},
    {"help", cell_help},
    {"env", cell_env},
    {"exit", cell_exit},
    {NULL, NULL}
};

static int cell_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "cell: expected argument to \"cd\"\n");
    }
    else if (chdir(args[1]) != 0)
    {
        perror("cell");
    }
    return 1;
}

static int cell_help(char **args)
{
    (void)args;
    p("Simple shell. Builtins:\n");
    for (int i = 0; g_builtins[i].name; i++)
        p("  %s\n", g_builtins[i].name);
    return 1;
}

static int cell_env(char **args)
{
    (void)args;
    for (char **env = environ; *env; env++)
        p("%s\n", *env);
    return 1;
}

static int cell_exit(char **args)
{
    (void)args;
    return 0;
}

static int cell_launch(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        execvp(args[0], args);
        perror("cell");
        exit(EXIT_FAILURE);
    }
    if (pid < 0)
    {
        perror("cell");
        return 1;
    }
    do
    {
        waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));

    return 1;
}

static int cell_execute(char **args)
{
    if (args[0] == NULL)
        return 1;

    for (int i = 0; g_builtins[i].name; i++)
    {
        if (strcmp(args[0], g_builtins[i].name) == 0)
            return g_builtins[i].func(args);
    }
    return cell_launch(args);
}

static char *cell_read_line(void)
{
    char *buf;
    size_t bufsize;
    char cwd[BUFSIZ];

    buf = NULL;
    bufsize = 0;

    Getcwd(cwd, sizeof(cwd));
    p(BRIGHT_BLUE "%s" RST " -> ", cwd);
    fflush(stdout);
    if (getline(&buf, &bufsize, stdin) == -1)
    {
        free(buf);
        if (feof(stdin))
            return NULL;
        perror("cell");
        return NULL;
    }
    return buf;
}

int main(void)
{
    char *line;
    char **args;
    int status;

    printbanner();
    status = 1;
    while (status && (line = cell_read_line()))
    {
        args = cell_split_line(line);
        status = cell_execute(args);
        free(args);
        free(line);
    }

    return EXIT_SUCCESS;
}
