/*
Homework 3
-----------
Write another program using fork(). The child process should print
"hello"; the parent process should print "goodbye". Try to ensure
that the child always prints first *without* using wait().

The obvious solution is wait(), but the homework specifically says
not to use it. Nya... so we need another synchronization mechanism.

While reading the chapter, I noticed a short section mentioning the
kill() system call and signals.

    int kill(pid_t pid, int sig);

The name "kill()" is honestly terrible. It doesn't necessarily kill
anything. It simply *sends a signal* to another process. Whether the
process dies depends entirely on which signal is sent.

So the next question became:

"What signals are available?"

Running:

    $ kill -l

gave me:

    HUP INT QUIT ILL TRAP ABRT BUS FPE KILL USR1 SEGV USR2
    PIPE ALRM TERM CHLD CONT STOP ...

My first thought was:

"Maybe I can pause the parent with SIGSTOP and resume it later with
SIGCONT."

GNU says:

    SIGCONT resumes a process that was previously stopped by SIGSTOP
    or SIGTSTP.

That sounded perfect... until I thought about it a little more.

The problem is that SIGCONT only resumes a process that is *already*
stopped. Nothing in my program naturally puts the parent into that
state, so I'd have to manually stop it first. At that point I'm
basically trying to recreate what wait() already gives me.

Back to the scratching post...

Then I discovered pause().

pause() suspends the current process until *any* signal is delivered.

Now the synchronization became much cleaner.

The parent does this:

    pause();

and literally falls asleep.

Meanwhile the child:

    1. prints "hello"
    2. sends SIGUSR1 to its parent

        kill(getppid(), SIGUSR1);

Notice the use of getppid() instead of getpid().

    getpid()   -> my PID
    getppid()  -> my parent's PID

So the child isn't killing itself.
It's simply telling the kernel:

    "Hey! Tell my parent I'm finished!"

The parent registers a signal handler before calling pause():

    signal(SIGUSR1, handler);

This tells the kernel:

    "If this process ever receives SIGUSR1, don't terminate me.
     Instead, run handler()."

The handler itself is empty.

Why?

Because we don't actually care about executing code inside the handler.
We only care that receiving the signal interrupts pause().

Timeline:

Parent:
    register SIGUSR1 handler which is a custom signal that says that SIGUSR1 calls our handler function instead of terminating
    pause() ---------------------------+
                                       |
Child:                                 |
    printf("hello");                   |
    kill(getppid(), SIGUSR1); ---------+ // Hey send the SIGUSR1 signal to the parent
                                       |
Kernel:
    delivers SIGUSR1
    runs handler()
    pause() returns
    parent prints "goodbye"

The signal isn't being used to send information.

It's simply acting as a synchronization event:

    "Meow! I'm done! You can continue now."

Pretty neat.

It is weird to kind of stretch your mind around. Why would an empty function be required to send a signal. The truth is I agree it is strange.
We need to bind this signal to some function. Printing out signal received helps give this function some meaning. The function is just a required argument for the signal function.
Technically just existing and not doing anything still qualifies you as "something?"
Who knew we would be getting so philosophical over what qualifies as "somethingness". 
```
*/


#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

void handler(int sig)
{
    printf("Signal Received\n");
}

int main()
{
    signal(SIGUSR1, handler);
    int rc = fork();

    if (rc < 0)
    {
        printf("We have a bad fork! \n");
    }
    else if(rc == 0)
    {
        printf(" hello ");
        kill(getppid(),SIGUSR1);
    }
    else
    {
        pause();
        printf(" goodbye ");
    }
    
    return 0;
}