#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
   FILE* file = fopen("file.txt", "w");
   if(!file) perror("Cannot open the file.\n");

    char text[] = "1234567";
    
    fclose(file);
    int* a = NULL;
    printf("file: %p \n", a);
    int count_of_written_objects = fwrite(text, sizeof(text),1, file);
    printf("Count of written objects into the file: %d \n", count_of_written_objects);
    
    if(count_of_written_objects != 1) perror("Not expected count of objects was written.\n");

    int success = fflush(file);
    printf("Variable success: %d \n", success);
    if(success == EOF) perror("Flush did not succeed. \n");



    return 0;
}
