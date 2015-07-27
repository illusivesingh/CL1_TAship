#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void main()
{
    int my_Pipe_Fd [2]; /* my_Pipe_Fd [0] contains the file descriptor
        * for reading, 
        * my_Pipe_Fd [1] contians the file descriptor for writing. */
    char buf [20] = {'\0'};
    char *hello = "Hello World";
    
    pid_t pid; /* Process id of the child process. */
    
    pipe (my_Pipe_Fd); // Initialize the File Descriptors.
    
    pid = fork ();
    
    if (pid == 0)
    {
        /* Child process. */
        write (my_Pipe_Fd [1], hello , strlen (hello));
    }
    else
    {
        /* parent process. */
        read (my_Pipe_Fd [0], buf, 17);
        printf ("%s aa \n", buf);
    }
}

