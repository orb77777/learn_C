#include <stdio.h>

int main(int argc, char* argv[])
{
    char* file_name = argv[1];
    FILE* file_stream = fopen(file_name, "r");

    int character_read;
    int new_line_counter = 1;
    while((character_read = getc(file_stream)) != EOF)
    {
        if(character_read == '\n')
        {
            new_line_counter++;
        }

    }

    fclose(file_stream);

    printf("A fájlban levő sorok száma: %d \n", new_line_counter);


    return 0;
}
