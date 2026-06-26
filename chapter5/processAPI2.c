#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("hello (pid:%d)\n",(int) getpid());
        /*
        The fork system call is os way to create a new process.
        It is almost an exact copy of the parent address
        */
        int rc =fork();
        if (rc < 0)
        {
            // Fork failed
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        else if (rc == 0) 
        {
            /*
            The Child does not start running at main() but instead starts 
            starts after the fork basically acting as if it called fork on its self
            */
            // child (new preocess)
            printf("child (pid:%d)\n", (int) getpid());
        }
        else
        {
            int rc_wait = wait(NULL);
            // parent goes down this path (main)
            printf("parent of %d  (rc_wait:%d) (pid:%d)\n",rc, rc_wait, (int) getpid());
        }
        return 0;
}