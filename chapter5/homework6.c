/*
Write a slight modification of the previous program, this time us-
ing waitpid() instead of wait(). When would waitpid() be
useful?

wait() and waitpid()

The wait() system call suspends execution of the calling process until one of its children terminates. The call wait(&status) is equivalent to:

waitpid(-1, &status, 0);

The waitpid() system call suspends execution of the calling process until a child specified by pid argument has changed state.

you can change the behavior based off the number you pass. -1 means any of the child processes complete then continue.

but we can replace -1 with a specific pid in order to wait for a specific child 

Suppose you have

Parent
 ├── Child A (PID 1001)
 ├── Child B (PID 1002)
 └── Child C (PID 1003)

Then

waitpid(1002, NULL, 0);

means

"Ignore A and C. Only wake me when Child B exits." Super Cool

remember wait and waitpid are easiest to think of as jobs. Their jobs are to syncronize the parent with the child.

They have a secondary function of reporting that something happened, but does not provide an explanation of what exactly happened

That is where errno.h can help us out. 

When the kernel attempts to wait for the child process it will see their is no child and return a number

Seeing 10 is not helpful thus we can leverage the errno.h library to help us convert this number to something meaningful

Notice we induce this error on purpouse to show that the child cant call wait on its self if there in no other child processes

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    int rc = fork();
    int status = 0;

    if (rc < 0) {
        printf("Fork failed\n");
    }
    else if (rc == 0) {
        int rc_wait = waitpid(getpid(), &status, 0);

        printf("Child process: pid=%d, waitpid returned %d\n", getpid(), rc_wait);
        if (rc_wait == -1) 
        {
            printf("waitpid failed: %s\n", strerror(errno));
        }
    }
    else {
        int rc_wait = waitpid(rc, &status, 0);

        printf("Parent process: pid=%d, waitpid returned %d\n", getpid(), rc_wait);
    }

    return 0;
}