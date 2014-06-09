#include <stdio.h>

// a bejövő paramokra a korlát az int argc (2^32), de ha ennél több kell, akkor long argc, és az máris több, de a lényeg, hogy
// ez adja a felső határt.
int main(int argc, char* argv[])
{
    int i = 0;
   // a for-on belüli i deklarálás a C99-től engedélyezett, itt még fordítási hiba. 
   // C-ben nincs bool, hanem az 1-es az igaz, a 0 a hamis, és ezt is vizsgálja a ciklus feltételében.
   //ha csak a parmétereket akarom kiírni, akkor 1-től kell kezdeni, mert a 0. param a program neve
    for(i = 1; i < argc; i++)
    {
        printf("arg: %d, %s \n", i, argv[i]);
    }

    char* towns[] = {
        "Budapest", "Pecs",
        "Szeged", "Debrecen"};
  
    //
    //    NULL konstans a C-ben a null pointer jelölésére, ez ugye egy makró, egyéb jelölések: 0, (void *)0.
//    towns[0] = NULL;

    //ha tovább indexelek a tömbben, akkor seg. fault futáskor. Forsítási idejű hiba nincs. Ha csak 1-gyel hosszabb, akkor
    //csak a záró 0-t írja felül, de ez buffer overflow, bizonytalan működés
//    int num_towns = 6;
    
    int num_towns = 4;

    for(i = 0; i < num_towns; i++)
    {
        printf("Varosok: %d. %s \n",i, towns[i]);
    }


    //a karakter konstansokat int-ként kezeli, és ezért 1 intnyi helyen is tárolja, a karakter változók 1 bájtot foglalnak
    //mindig.
    printf("%d \n",sizeof('üaaa'));// ezt már nem tudja 4 bájton (int) eltárolni, túlcsordul => bizonytalan viselkedés. Persze méretre így is 4 bájtot ír ki.

    // részfeladat magamnak: fordítsam meg az egyik string betűit. Vigyázat! csak úgy működik, ha a string tömb nem char* x[],
    // mert a char* read-only példányokat csinál, amit egy megosztott szegmensre tesz. Ha ennek tartalmát akarom módosítani,
    // akkor seg. faultot ad, mert nem módosítható az a szegmens. A char [x][y] pedig létrehoz egy tömböt, aminek a tartalma
    // módosítható, mint egy sima típusé.
    /*
    int j = 0;
    char depo;
    int size = sizeof(towns[0]);

    printf("%d \n", size);
    for(i = 0, j = size - 1; i < j; i++, j--)
        {
            depo = towns[0][i];
            towns[0][i] = towns[0][j];
            towns[0][j] = depo;
        }

    printf("%s \n", towns[0]);
    */
    return 0;
}
