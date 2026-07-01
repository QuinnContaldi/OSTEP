#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

void Print_Array(char* array);
void Print_Buffer(char* array, size_t max);

#define MAX 20
int main()
{
    char userinput[MAX];
    char username[MAX];
    printf("Welcome to Dr.Meowras shell! enter in your username!: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    do
    {
        printf("%s@MEOW----> ",username );
        if(fgets(userinput, sizeof(userinput), stdin) == NULL)
            return 1;

        userinput[strcspn(userinput,"\n")] = '\0';
        Print_Array(userinput);
        Print_Buffer(userinput, MAX);

        int rc = fork();

        if(rc < 0)
        {
            printf("fork failed\n");
        }
        else if(rc == 0 ) 
        {
            printf("parent pid: %d of child pid: %d\n",getpid(), rc);
        }
        else
        {
            printf("currently in child pid %d\n", getpid());
        }

        
    }
    while( (strcmp(userinput, "exit") && strcmp(userinput, "Exit")) );

    return 0;
}

void Print_Buffer(char *buffer, size_t max)
{
    printf("********PRINT BUFFER********\n");
    // Top border
    for (size_t i = 0; i < max; i++)
        printf("+----");
    printf("+\n");

    // Contents
    for (size_t i = 0; i < max; i++)
    {
        printf("|");

        if (buffer[i] == '\0')
            printf(" \\0 ");
        else if (buffer[i] == '\n')
            printf(" \\n ");
        else if (buffer[i] == '\t')
            printf(" \\t ");
        else if (buffer[i] >= 32 && buffer[i] <= 126)
            printf(" %c  ", buffer[i]);
        else
            printf(" ?? ");
    }
    printf("|\n");

    // Bottom border
    for (size_t i = 0; i < max; i++)
        printf("+----");
    printf("+\n");
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