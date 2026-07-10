#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

void Print_Array(char* array);
void Print_Buffer(char* array);
void Clean_Array(char* array);
void Clean_Command(char* array,char* commands);

#define MAX 40
int main()
{
    char userinput[MAX];
    char username[MAX];
    char commandarray[MAX];
    printf("Welcome to Dr.Meowras shell! enter in your username!: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    do
    {
        printf("%s@MEOW----> ",username );
        Clean_Array(userinput);
        if(fgets(userinput, sizeof(userinput), stdin) == NULL)
            return 1;
        userinput[strcspn(userinput,"\n")] = '\0';
        Print_Array(userinput);
        Print_Buffer(userinput);
        Clean_Command(userinput,commandarray);

        int rc = fork();

        if(rc < 0)
        {
            printf("Meaning wait failed producing error %s\n", strerror(errno)); 
        }
        else if(rc == 0 ) 
        {
            printf("In child PID: %d\n" ,getpid());
            execl("meow", "meow", (char *)NULL);
        }
        else
        {
            printf("Currently in Parent PID: %d, Child PID: %d\n", getpid(), rc);
            wait(NULL);
        }

        
    }
    while( (strcmp(userinput, "exit") && strcmp(userinput, "Exit")) );

    return 0;
}

void Print_Array(char *array)
{
    printf("********PRINT ARRAY********\n");
    size_t length = 0;

    // Find the length
    length = strnlen(array,MAX);

    // Top border
    for (size_t i = 0; i <= length; i++)
        printf("+----");
    printf("+\n");

    // Contents
    for (size_t i = 0; i < length; i++)
    {
        printf("|");

        if (array[i] == '\n')
            printf(" \\n ");
        else if (array[i] == '\t')
            printf(" \\t ");
        else
            printf(" %c  ", array[i]);
    }

    // Print the null terminator
    printf("| \\0 |\n");

    // Bottom border
    for (size_t i = 0; i <= length; i++)
        printf("+----");
    printf("+\n");

    // Index row
    for (size_t i = 0; i <= length; i++)
        printf(" %2zu  ", i);

    printf("\n\n");
}

void Print_Buffer(char *buffer)
{
    printf("********PRINT BUFFER********\n");
    // Top border

    for (size_t i = 0; i < MAX; i++)
        printf("+----");
    printf("+\n");

    // Contents
    for (size_t i = 0; i < MAX; i++)
    {
        printf("|");

        if (buffer[i] == '\0')
            printf(" \\0 ");
        else if (buffer[i] == '\n')
            printf(" \\n ");
        else if (buffer[i] == '\t')
            printf(" \\t ");
        else
            printf(" %c  ", buffer[i]);
    }
    printf("|\n");

    // Bottom border
    for (size_t i = 0; i < MAX; i++)
        printf("+----");
    printf("+\n");
}


void Clean_Array(char *buffer)
{
    size_t length;

    // Find the length
    length = strnlen(buffer,MAX);
    for (size_t i = 0; i < length; i++)
        buffer[i] = ' ';
}

void Clean_Command(char* array, char* commands)
{
    size_t length;

    // Find the length
    length = strnlen(array,MAX);

    for(size_t i = 0; i < length; i++)
    {
        if (array[i] == '\0' || array[i] == '\n'|| array[i] == '\t' || array[i] == ' ')
            array[i] = '\0';
        else
            commands[i] = array[i];
        Print_Buffer(array);
        Print_Buffer(commands);
    }
}