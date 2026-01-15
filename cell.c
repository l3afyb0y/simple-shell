
#include "cell.h"
#include <stdio.h>


int main(int ac, char **av)
{
    (void)ac;
    int status;

    // do this in a LOOP!
    // child process
    if (fork() == 0)
        // replace the current process image with a new process image
        //v for "vector", p for "path"
        //Take an array of arguments and uses PATH to find the excutable
        // char **av = {}"ls", "-la", NULL};
        // execvp("ls", av);
        //TLDR: Duplicate yourself, change yourself with the "ls" command, with this (-la) input.
        //The father is going to wait for the child, stalk the (&status) then return child value
        
        execvp(av[1], av + 1);

    wait(&status);

    return EXIT_SUCCESS; /* E: use of  undeclared identifier 'EXIT_SUCCESS*/
}