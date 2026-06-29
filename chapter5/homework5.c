/*
 Now write a program that uses wait() to wait for the child process
to finish in the parent. What does wait() return? What happens if
you use wait() in the child

*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
    int rc = fork();

    if (rc < 0) {
        printf("Fork failed\n");
    }
    else if (rc == 0) {
        int rc_wait = wait(NULL);
        printf("Child process: pid=%d, wait returned %d\n", getpid(), rc_wait);
        if(rc_wait == -1)
            printf("Meaning wait failed producing error %s\n", strerror(errno));
    }
    else {
        int rc_wait = wait(NULL);
        printf("Parent process: pid=%d, wait returned %d\n",
               getpid(), rc_wait);
    }

    return 0;
}