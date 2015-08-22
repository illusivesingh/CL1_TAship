#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Important Note:
 *  The child inherits copies of the parent's set of open file 
 *  descriptors.  
 *  Each file descriptor in the child refers to the same open file  
 *  description (see open(2)) as the corresponding file descriptor in 
 *  the parent.  This means that the two descriptors share open file 
 *  status flags, current file offset, and signal-driven I/O attributes 
 * (see the description of F_SETOWN and F_SETSIG in fcntl(2)).        
 * 
 *  HENCE:
 *      Both parent and child may try to read and write at terminal 
 *  simultaneously.
 */



void main()
{
    int save_STDIN; /* Stores the orignal file descriptor to this . */
    
    save_STDIN = dup (0); /* Duplicates the file descriptor 0 to 
        * and returns its index, which is saved in save_STDIN. */
        
    /* for stdin we have two copies, one in index 0 and other in 
     * index save_STDIN. */
     
    /* System always reads from the file desriptor 0. */
    
    /* Now we replace index 0 with our own file to redirect input to 
     * the targed file. */
    
    /* Using dup2 (src, dest).
     *      we can copy the source file descriptor to the destination.
     *      make dest also connet to what src is already connected to. 
     * */
     
    // Make two pipes.
    int my_Pipe1 [2]; // used by child for reading 
    int my_Pipe2 [2]; // used by main for reading.
    
    pipe (my_Pipe1); /* Get read and wriet file descriptors for my_Pipe1
        */
    pipe (my_Pipe2); /* File descriptors for my_Pipe2. */
    
    pid_t pid; // pid of the child process.
    
    pid = fork (); // create new process.
    
    int save_Stdin; // back up storage of stdin.
    int save_Stdout; // back up storage of stdout.
    
    if (pid == 0)
    {
        // Child process
        
        /* Copy std in to save_Stdin and std out to save_Stdout for 
         * back up, since we may need to use them later. */
        save_Stdin = dup (STDIN_FILENO);
        save_Stdout = dup (STDOUT_FILENO);
        
        /* Make the stdin of this process read from my_Pipe1. */
        /* dup2 (my_Pipe1 [0], STDIN_FILENO); /* STDIN_FILENO shall read
            * from the file mentioned in my_Pipe1 [0]. */
        
        /* Now both my_Pipe1 [0] and STDIN_FILENO are trying to read 
         * from the same file.
         * So we are trying to read the same thing twice. */
        
        close (my_Pipe1 [0]); /* close my_Pipe1 from reading. */
        
        /* Redirecting the output. 
         *      Child shall not try to read from the my_Pipe2 since 
         * parent shall read from the my_Pipe2 and child shall write
         * into it. */
        close (my_Pipe2 [0]); /* close my_Pipe2 from reading. */
        
        /********** WRITING **************/
        
        /* Child shall write into the same file as that of my_Pipe2 [1]
         * and shall not use the writing end of my_Pipe1 at all. */
         
        /* Redirect the standard output to the file in my_Pipe2 [1]. */
        dup2 (my_Pipe2 [1], STDOUT_FILENO);
        
        /* Close the output end of my_Pipe2 since other wise we will be
         * trying to write to a file twice once via STDOUT_FILENO and
         * second time via my_Pipe [2]. */
        
        close (my_Pipe2 [1]); // Because it has been duplicated.
        close (my_Pipe1 [1]); // Because it shall not be touched.


        printf ("Hello\n");
    }
    else
    {
        // parent process
        /* Backup stdin and stdout. */
        save_Stdin = dup (STDIN_FILENO);
        save_Stdout = dup (STDOUT_FILENO);

        /* parent shall read from the reading end of my_Pipe2. */
        dup2 (my_Pipe2 [0], STDIN_FILENO);
        
        /* close the reading ends of pipes. */
        close (my_Pipe1 [0]); // Becasue it shall not be touched.
        close (my_Pipe2 [0]); // Because stdin is already reading from it.
        
        
        /* parent shall write to the file pointed by writing end of 
         * my_Pipe2. */
         
        // dup2 (my_Pipe1 [1], STDOUT_FILENO);
        
        /* Close the writing ends of the pipes. */
        
        close (my_Pipe2 [1]); // Because it shall not be touched.
        close (my_Pipe1 [1]); // Because it has aready been redirected.
        
        sleep (3);
        
        char s[20] = {'\0'};
        scanf ("%s", s);
        
        printf ("parent printing %s\n", s);
    }
}


