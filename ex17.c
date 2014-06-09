#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address
{
    long id;
    int is_set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database
{
    struct Address rows[MAX_ROWS];
};

struct Connection
{
    FILE* file_stream;
    struct Database* db;
};

void die(char* error_message)
{
    if(errno)
    {
        perror(error_message);
    }
    else
    {
        printf("You've got an error: %s \n", error_message);
    }

    exit(2);

}


void Database_load(struct Connection* connection)
{
    int number_of_read_objects = fread(connection->db, sizeof(struct Database), 1, connection->file_stream);
    if(number_of_read_objects != 1)
    {
        die("Database loading failed. \n");
    }
}

struct Connection* Database_open(char* filename, char action)
{
    struct Connection* connection = malloc(sizeof(struct Connection));
    if(!connection)
    {
        die("Memory error.");
    }

    connection->db = malloc(sizeof(struct Database));
    if(!connection->db)
    {
        die("Memory error. \n");
    }

    if(action == 'c')
    {
        connection->file_stream = fopen(filename, "w");
    }
    else
    {
        connection->file_stream = fopen(filename, "r+");

        if(connection->file_stream)
        {
             Database_load(connection);
        }
    }
    
    if(!connection->file_stream)
    {
        die("File opening error. \n");
    }

    return connection;
}


void Database_create(struct Connection* connection)
{
    int i = 0;

    for(i = 0; i < MAX_ROWS; i++)
    {
        struct Address row = {.id = i, .is_set = 0};
        connection->db->rows[i] = row;
    }
}

void Database_write(struct Connection* connection)
{
    // a streamet a fájl elejére pozicionálja.
    rewind(connection->file_stream);

    int number_of_written_objects = fwrite(connection->db, sizeof(struct Database), 1, connection->file_stream);
    
    if(number_of_written_objects != 1)
    {
        die("Failed to write on the stream \n");
    }

    int check = fflush(connection->file_stream);

    if(check == EOF)
    {
        die("Failed to write in the file. \n");
    }
}

void Address_print(struct Address* address)
{
    //A printf-nek a "" jeleknek egy sorban kell lenniük, nem lehet sortörés!
    // Unsigned long kiíratása: %lu, signed long kiíratása: %ld
    printf("id: %ld \n name: %s \n  email: %s \n", 
            address->id, address->name, address->email);
}

void Database_get(struct Connection* connection, long id)
{
    struct Address* row = &connection->db->rows[id];

    if(row->is_set)
    {
        Address_print(row);
    }
    else
    {
        die("ID is not set. \n");
    }
}

void Database_set(struct Connection* connection, int id, char* name, char* email)
{
    struct Address* address = &connection->db->rows[id];

    if(address->is_set)
    {
        die("Already set, delete it first.");
    }
    address->is_set = 1;
    /*
     * char* strncpy(char* to, const char* from, size_t size) -> return: a stringet adja vissza, amit másolt, ha semmit, akkor
     * NULL. Előnyösebb ezt használni, mint a strcpy-t, mert az utóbbi mindent átmásol a from-ból, akkor is, ha az nem fér bele
     * a to-ba (ilyenkor felülírja a lezáró nullát, aztán elszáll a progi). Átlapolódáskor mindkettő viselkedése bizonytalan. 
     * Ez viszont max annyit másol át, amennyit megadunk neki. 
     *
     * !Ha a from nagyobb mint amennyit át akarunk másolni, akkor a másolt string nem lesz lezárva 0-val!
     * Ha többet másolunk, mint amilyen nagy a from, akkor a maradékot kitölti 0-val. 
     * Ez csak akkor előnytelen, ha sokkal kisebb a from mint amennyit másolni akarunk, mert ekkor sok időt veszteget arra, hogy
     * a maradékot kitöltse nullával.
     * */
    char* copied = strncpy(address->name, name, MAX_DATA);

    if(!copied)
    {
       die("Name copy failed.");
    }

    copied = strncpy(address->email, email, MAX_DATA);

    if(!copied)
    {
        die("Email copy failed.");
    }


}

void Database_delete(struct Connection* connection, int id)
{
    struct Address* address = &connection->db->rows[id];

    // KIEG a példaprogihoz: csak azt lehessen törölni, ami egyszer már be volt állítva.
    if(!address->is_set)
    {
        die("Is not set, you can't delete it.");
    }

    address->is_set = 0;

}

void Database_list(struct Connection* connection)
{
    int i = 0;
    for(i = 0; i < MAX_ROWS; i++)
    {
        if(connection->db->rows[i].is_set)
        {
            Address_print(&connection->db->rows[i]);
            printf("\n");
        }
    }
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        printf("USAGE: ex17 <dbfile> <action> [db params] \n");
        exit(1);
    }

    /*
     * Helytelen inicializálása egy tömbnek: char filename[] = argv[1]; 
     * A tömböt ugyanis csak konstans kifejezésekkel lehet inicializálni (konstans string, értékek), de egy másik változóval
     * nem. Ezt strcpy()-val kell megoldani, ha char tömbről van szó.
     * */
    char* filename = argv[1];
    char action = argv[2][0];
    struct Connection* connection = Database_open(filename, action);
    long id = 0;

    if(argc > 3)
    {
        char* end;

        //Ha a szám túlcsordul, akkor beállítja az errno-t a strtol. Ahhoz, hogy tesztelni tudjuk, hogy volt-e
        //ilyen, le kell nullázni az errno-t, mivel más fgv, már beállíthatta valamilyen hibával korábban.
        errno = 0;
        /*
         * Az atoi() elavult, nem javasolt a használata, nehézkessé teszi a hibakeresést. Nem lehet megkülönböztetni, mikor 
         * nem sikerült az átalakítás, ill. mikor alakított át egy stringet 0-ra, mert mindkettőnél 0-t ad vissza.
         * 
         * strtol(const char* átalakítandó, char** tailpointer, int base) -> return: a longgá alakított string.
         * A tailpointerrel lehet ellenőrizni, hogy sikerült-e az átalakítás: ha igen, akkor a lezáró 0-n áll (ami 0). 
         * Ha nem, akkor a tailpointerbe rakja bele, hogy melyik részét nem sikerült átalakítania.
         * A base-ben a számrendszert kell megadni, amilyenbe akarjuk. A 0 is a 10-est jelöli.
         * */
        id = strtol(argv[3], &end, 10);

        if(errno)
        {
            die("Overflow.");
        }

        if(*end)
        {
            printf("Conversion error, non-convertible part: %s \n", end);
        }
    }

    switch(action)
    {
        case 'c':
            //hiba az eredetiben, nincs alsóvonás a fgv. névben.
            Database_create(connection);
            Database_write(connection);
            break;

        case 'g':
            if(argc != 4)
            {
                die("You need an ID to get the content of a row. \n");
            }
            Database_get(connection, id);
            break;

        case 's':
            if(argc != 6)
            {
                die("You need an ID, name and email to set \n");
            }
            Database_set(connection, id, argv[4], argv[5]);
            Database_write(connection);
            break;
        case 'd':
            if(argc != 4)
            {
                die("You need an ID to delete the content.");
            }
            Database_delete(connection, id);
            Database_write(connection);
            break;
        case 'l':
            Database_list(connection);
            break;
        default:
            die("Invalid action: c=create, g=get, s=set, d=delete, l=list ");
    }

    Database_close(connection);

    return 0;
}
