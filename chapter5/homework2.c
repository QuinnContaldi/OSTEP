#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
Write a program that opens a file (with the open() system call)
and then calls fork() to create a new process. Can both the child
and parent access the file descriptor returned by open()? What
happens when they are writing to the file concurrently, i.e., at the
same time?
*/
#define MAX 100

int main()
{
    int fd = open("catgirl_roleplay.txt", O_RDWR | O_APPEND);
    int len = 0; 
    char buffer[MAX];
    for (int i =0; i < MAX;i++ )
        buffer[i] = ' ';
    printf("Meow we are opening the fwile owo curwent return status is %d\n", fd);
    int rd = fork();

    if(rd < 0)
    {
        printf("fork fucking failed uwu\n");
    }
    else if (rd == 0) {
        len = snprintf(buffer, sizeof(buffer),"Meow Meow I am child process %d\n", (int)getpid());
        write(fd, buffer, len);
        printf("fork called Child PID %d, file discription %d\n",(int)(getpid()), fd);
    }
    else {
        len = snprintf(buffer, sizeof(buffer), "Im in the parent process %d\n", (int)(getpid()));
        write(fd, buffer, len);
        printf("fork called Parent PID %d, file discription %d\n",(int)(getpid()), fd);
    }


}