#include <stdio.h>

int main(int argc, char* argv[])
{

    //ha nem inicializálom az i-t, és úgy használom, akkor bizonytalan lesz a működés, lehet, h 0 lesz benne, de lehet más is.
    //A globális és a static int változókat 0-ra inicializálja mindig, a lokálisakat nem biztos.
    int i = 1;

    printf("%d \n", i);
    while(i < argc)
    {
        printf("Paraméterek: %d. %s \n", i, argv[i]);
        i++;

    }

    
    //visszafelé olvasom ki a parmétereket:
    i = argc - 1;
    while(i > 0)
    {
        printf("Paraméterek: %d. %s \n", i, argv[i]);
        i--;

    }

    int num_towns = 4;
    char* towns[] = {
        "Budapest", "Pecs",
        "Szeged", "Debrecen"
    };

    i = 0;

    while(i < num_towns)
    {
        printf("Városok: %d. %s \n", i, towns[i]);
        //ha nem növelem az i-t, akkor végtelen ciklus!
        i++;
    }

    //+FELADAT: a towns és az argv tömböt egyesíteni.
    i = 0;

    printf("A városok tömb mérete: %lu \n", sizeof(towns));
    //Ez hibás így, seg. faultot ad, hiszen a towns hosszát ő 4-re inicializálta, és még a lezáró 0-t átírja, de utána már a
    //pointer határkörén kívülről akarok elérni területeket! Meg kell kézzel csinálni, amit a Java pl automatikusan: létrehozni
    //egy új tömböt, amit az új hosszal inicializálok, és abba másolni az új értékeket.
    /*
    while(i < argc)
    {
//        towns[num_towns] = argv[i];
        i++;
        num_towns++;
    }
   */

    int size_of_towns_and_args = num_towns + (argc - 1);
    if(size_of_towns_and_args > 10)
    {
        size_of_towns_and_args = 10;
    }
    printf("Az egyesített tömb mérete: %d \n", size_of_towns_and_args);
    //meg kell adnom a méretét is, ha nem inicializálom, különben nem tudja, mennyit foglaljon, fordítási hiba.
    char* towns_and_args[size_of_towns_and_args];
    while(i < size_of_towns_and_args)
    {
        if(i < num_towns)
        {
             towns_and_args[i] = towns[i]; 
             i++;
             continue;
        }

        towns_and_args[i] = argv[i - num_towns + 1];
        i++;
    }

    i = 0;
    while(i < size_of_towns_and_args)
    {
        printf("Egyesített tömb elemei: %d. %s \n", i, towns_and_args[i]);
        i++;
    }

    return 0;
}
