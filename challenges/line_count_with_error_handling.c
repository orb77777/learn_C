#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char* argv[])
{
    // A program nevét is beleszámolja!
    if(argc != 2)
    {
        printf("USAGE: <PROGRAM> <FILE>");
        exit(1);
    }
    char* file_name = argv[1];
    FILE* file_stream = fopen(file_name, "r");
    assert(file_stream);

    int character_read;
    //mert az utolsó sorban nincs ENTER
    int new_line_counter = 1;
    while((character_read = getc(file_stream)) != EOF)
    {
        if(character_read == '\n')
        {
            new_line_counter++;
        }

    }

    int c = fclose(file_stream);
    if(c == EOF)
    {
        printf("Failed to close the file stream. \n");
        exit(2);
    }

    printf("A fájlban levő sorok száma: %d \n", new_line_counter);


    return 0;
}
