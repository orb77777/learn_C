#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef int (*compare)(int number1, int number2);

void die(const char* error_message)
{
    if(errno)
    {
        perror(error_message);
    }
    else
    {
        printf("%s \n", error_message);
    }

    exit(1);

}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        die("<USAGE: ex18 4 6 1 5>");
    }

    int count = argc -1;
    int* numbers = malloc(count * sizeof(int));
    if(!numbers)
    {
        die("Memory error (1)");
    }

    int i = 0;
    char** input_string = argv + 1;
    char* tail_pointer;
    
    for(i = 0; i < count; i++)
    {
        errno = 0;

        numbers[i] = strtol(input_string[i], &tail_pointer, 10);

        if(errno)
        {
            die("Overflow.");
        }

        if(*tail_pointer)
        {
            die("Input string conversion failed.");
        }
    }


    return 0;
}
