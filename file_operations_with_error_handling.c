#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
   FILE* file = fopen("file.txt", "w");
   //teszteset: olvasásra megnyitni egy nem létező fájlt, az NULL-t ad.
   if(!file) perror("Cannot open the file.\n");

    char text[] = "1234567";
    printf("A text mérete: %lu \n", sizeof(text));
    fclose(file);

    //teszteset: fwrite előtt legyen az fclose. A program nem száll el, lefut, az fwrite ráír a streamre???(csak tipp, mert
    //a count rendben van, de valgrinddel való futtatásnál jelzi a hibát), csak a fájlbaírás
    //nem történik meg. Mivel a streamre ráírja ? a megfelelő mennyiségű (count) adatot, azért annak vizsgálatával nem szűrhető
    //ki a hiba. De! Mivel a stream már le volt zárva a fájlhoz, ezért a fájlnak a leírója (file descriptor) nem érvényes, és
    //hibaüzenettel jelzi ezt az errno beállításával: az az EBADF makró.
    int count_of_written_objects = fwrite(text, sizeof(text),3, file);
    if(close(errno = EBADF)) perror("Invalid file descriptor.\n");
    printf("Count of written objects into the file: %d \n", count_of_written_objects);
    
    //teszteset: csak olvasásra van megnyitva a fájl, és írni akarunk bele (vagy fordítva), ekkor 0-t írt bele.
    //"Bad file descriptor" hibát kapunk (EBADF makró).
    if(count_of_written_objects != 1) perror("Not expected count of objects was written.\n");

    //sleep(5);

    printf("file: %p \n", file );
    char* name = "Andi";
    char* p = strdup(name);
    printf("P before free: %p \n", p);
    free(p);
    printf("P after free: %p \n", p);
    
    //if(file == NULL) perror("Stream is NULL. \n");
    int success = fflush(file);
    printf("Variable success: %d \n", success);
    if(success == EOF) perror("Flush did not succeed. \n");



    return 0;
}
