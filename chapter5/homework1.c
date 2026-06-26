/*rite a program that calls fork(). Before calling fork(), have the
main process access a variable (e.g., x) and set its value to some-
thing (e.g., 100). What value is the variable in the child process?
What happens to the variable when both the child and parent change
the value of x?
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int catgirl = 100;
    
    printf("hello (pid:%d)\n",(int) getpid());
        int rc = fork();
        
        if (rc < 0){
            printf("fork failed");
        }
        else if (rc == 0) {
            catgirl = 300; 
            printf("Child process: %d current value of catgirl is %d\n", (int) (getpid()), catgirl);
        }
        else {
            printf("Parent proccess: %d current value of catgirl is %d\n", (getpid()), catgirl);
        };
        printf("pid:%d final catgirl:%d\n", (int)getpid(), catgirl);
}