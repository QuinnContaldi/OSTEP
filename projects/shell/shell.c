#include <stdio.h>
#include <string.h>

int main()
{
    char userinput[500];
    //Current goal is to build something that accepts user input 
    if(fgets(userinput, sizeof(userinput), stdin) != NULL)
        printf("you typed %s\n", userinput);
    userinput[3] ='\0';
        printf("Removed a letter %s\n", userinput);
}