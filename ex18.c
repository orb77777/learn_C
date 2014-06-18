#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*
 * Függvénypointer típus definiálása. Így könnyen adható át függvény paraméterben.
 *
 * A fgv. pointer minden olyan fgv.-re illeszkedik, aminek a szignatúrája (kivéve a nevét) megegyezik
 * az övével. Jó, mert pl. ebben a programban is a bubble_sort fgv. megkaphat egy ilyen fgv. pointer típusú fgv.-t, és 
 * az értékétől függően fog lefutni az adott típusú sorrendberakás. Előnyei:
 * - olvashatóbb kód, nem kell flag-ekkel megkülönböztetni, és elágazásokkal a kül. módokat
 * - magasabb absztrakciós szinten lehet megírni az adott fgv. kódját, az elágazó implementáció
 *   külön fgv-ekben kezelhető, amiket a fgv. pointer fog össze.
 * - összegyűjthetőek vele az azonos funkciójú függvények, mintha csak egy interface-t adna rájuk. 
 * */
typedef int (*cmp)(int number1, int number2);

/*
 * A rendezési algoritmusokra mutató fgv. pointer.
 * */
typedef int* (*srt)(int*, int, cmp);

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

int* bubble_sort(int* numbers, int count, cmp compare)
{
    int i = 0;
    int j = 0;
    int temp = 0;
    /*
     * A második ciklussal elég csak i-vel kevesebb lépést megtenni, mert minden külső ciklus lépéssel
     * egy elem biztos a helyére kerül.
     * A -1 kell a második ciklusban, mert j+1 van, és így kiindexelnék.
     * A külső ciklus csak egy számláló szerepet tölt be, hogy minden elem biztosan sorra kerüljön.
     * */
    for(i = 0; i < count; i++)
        for(j = 0; j < count - i - 1; j++)
        {
            if(compare(numbers[j], numbers[j+1]) > 0)
            {
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }
        }

   return numbers;


}

int* insertion_sort(int* numbers, int count, cmp compare)
{
    int i = 0;
    int j = 0;
    int temp = 0;

    for(i = 0; i < count; i++)
        for(j = i; j > 0; j--)
        {
            if(compare(numbers[j-1], numbers[j]) > 0)
            {
                temp = numbers[j-1];
                numbers[j-1] = numbers[j];
                numbers[j] = temp;
            }
            // csak addig hasonlítgassunk visszafelé, a már rendezett tömbben, amíg már nem kell cserélni
            // mert ha egyszer nem kell, akkor utána se kell, a rendezettség miatt.
            else
            {
                break;
            }
        }

    return numbers;
}

void test_sorting(int* numbers, int count, cmp compare, srt sort)
{
    int* copied_numbers = malloc(count * sizeof(int));
    if(!copied_numbers)
    {
        die("Memory error (2).");
    }
    /*
     * void* memcpy(void* to, const void* from, size_t number_of_bytes) -> a visszatérési pointer a to-ra mutat.
     * Vigyázni kell, hogy a to és a from ne lapolódjon át, különben bizonytalan a viselkedés.
     * Átmásolja a from-ból a to által mutatott területre number_of_bytes mennyiségű adatot.
     * Stringeknél a strcpy vagy a strncpy, más tömbtípusoknál ez használandó másoláskor.
     * */
    memcpy(copied_numbers, numbers, count * sizeof(int));

    int* sorted_numbers = sort(copied_numbers, count, compare);

    int i = 0;

    for(i = 0; i < count; i++)
    {
        printf("%d ", sorted_numbers[i]);
    }

    printf("\n");

    free(copied_numbers);

    //Érdekesség:  a fgv. pointer által mutatott területet stringként olvasom ki, majd hexában 
    //kiíratom. Ezt aztán megnézhetem a futtatható fájlban, és meg lehet találni vele, hol kezdődik a függvény.
    unsigned char* data = (unsigned char*) compare;

    for(i = 0; i < 25; i++)
    {
        printf("%02x:", data[i]);
    }

    printf("\n");
}

int sorted_order(int a, int b)
{
    return a - b;
}

int reversed_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if(a == 0 || b == 0)
    {
        return 0;
    }

    return a % b;
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

    test_sorting(numbers, count, sorted_order, bubble_sort);
    test_sorting(numbers, count, reversed_order, insertion_sort);
    test_sorting(numbers, count, strange_order, insertion_sort);



    free(numbers);

    return 0;
}
