#include "cell.h"

// WRAPPERS

void    *Getcwd(char  *buf, size_t size)
    {
        if (NULL == getcwd(buf, size))
            perror(RED"getcwd FAILED");
        return buf;
    }



void *Malloc(size_t size)
{
    void *ptr;
    if (size == 0)
        return (NULL);
    ptr = malloc(size);
    if (!ptr)
    {
        perror(RED"malloc failed\n"RST);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void    *Realloc(void *ptr, size_t size)
{
    ptr = realloc(ptr, size);
    if (!ptr)
    {
        perror(RED"realloc failed\n"RST);
        exit(EXIT_FAILURE);
    }
    return ptr;
}


void    printbanner(void)
{
    p(BLUE"▄▖    ▌       ▌   ▜ ▜     ▗\n"
        "▙▌▛▌▛▘▙▘█▌▛▘▛▘▛▌█▌▐ ▐   ▌▌▜\n"
        "▌ ▙▌▌ ▛▖▙▖▌ ▄▌▌▌▙▖▐▖▐▖  ▚▘▟▖\n"RST);
}
