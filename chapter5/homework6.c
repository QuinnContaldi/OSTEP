 
 /*
 Nyah~ Homework 6: wait() vs waitpid()
 
 Assignment: Both wait() and waitpid() exist to synchronize a parent process with
 its child process(es). Their primary job is to make the parent patiently
 wait until the kitten (child process) has finished its important work.

 Dr. Meowra's Operating Systems Notes:
 
 
wait(&status) is equivalent to:  waitpid(-1, &status, 0);
 
The first argument to waitpid() determines WHICH child we are waiting for.
 
    -1  -> Wait for ANY Child to return home.
    PID -> Wait for ONE SPECIFIC child.
 
Example:

    Parent Cat
    ├── Kitten A (PID 1001)
    ├── Kitten B (PID 1002)
    └── Kitten C (PID 1003)

Calling:

    waitpid(1002, NULL, 0);

means:
    "Ignore the other fluffballs. Wake me only when Kitten B
    comes home safely."

  This makes waitpid() useful when the parent owns multiple child
  processes but only needs to synchronize with one of them.
 
  Return values:
    Child PID  -> Success! Nya~
    -1         -> Something went horribly meowrong.
    0         -> Only possible with WNOHANG when no child has exited.

Experiment:
I intentionally had the child execute:
    waitpid(getpid(), NULL, 0);

 This is equivalent to a kitten trying to wait for itself to come
 home. The kernel looks at the request and says:

    "Nya... that's not how families work."
 
 Since a process may only wait for ITS OWN CHILDREN (not itself),
 the kernel rejects the request and waitpid() returns -1.

To determine WHY it failed, inspect errno:
    if (waitpid(getpid(), NULL, 0) == -1)
        printf("%s\n", strerror(errno));

For this experiment the error is:
       "No child processes"
 
Internally, the kernel returns the error code ECHILD. The C library
stores that value in errno, and strerror(errno) translates it into
a human-readable string.
 
  Moral of the story:
    A responsible parent catgirl waits for its kittens.
    A kitten cannot wait for itself.
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