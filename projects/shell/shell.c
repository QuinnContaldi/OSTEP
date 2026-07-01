#include <stddef.h>
#include <stdio.h>
#include <string.h>

void Print_Array(char* array);
void Print_Buffer(char* array, size_t max);

#define MAX 20
int main()
{
    char userinput[MAX];
    char username[MAX];
    printf("Welcome to Dr.Meowras shell! enter in your username! \n");
    fgets(username, sizeof(username), stdin);

    do
    {
        printf("%s@MEOW----> ",username );
        if(fgets(userinput, sizeof(userinput), stdin) == NULL)
            return 1;

        Print_Buffer(userinput, MAX);
        printf("removing \\0\n");
        userinput[strcspn(userinput,"\n")] = '\0';
        Print_Array(userinput);
        
    }
    while( (strcmp(userinput, "exit") && strcmp(userinput, "Exit")) );


}

void Print_Buffer(char* buffer, size_t max)
{
    int index = 0;

    printf("******Array Contains******\n");

    for (char* p = buffer; p < buffer + max; p++, index++)
    {
        if (*p == '\n')
            printf("array[%d] = '\\n'\n", index);
        else
            printf("array[%d] = %c \n", index, *p);
    }
    printf("array[%d] = \\0\n\n\n\n", index);
};

void Print_Array(char* array)
{
    size_t size = strlen(array);
    int index = 0;

    for(char* p = array;
        p < array + size && *p != '\0';
        p++, index++)
    {
        printf("array[%d] = %c, ", index, *p);
    }
    printf("\n\n\n\n\n");
};
