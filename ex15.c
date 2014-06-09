#include <stdio.h> 

//A pointerekről:
    //Pointerbe tesszük bele a címet. Pointer: változó, ami az értékéül adott címre mutat. (itt: arra a területre mutatnak, ahol
    //a names és az ages "él" a szg. memóriájában.) Tehát a pointer egy cím, ami valahova mutat a memóriában + típus
    //meghatározás, hogy a mutatott adathoz a megfelelő nagyságot kapjuk meg. (Nyilván, gondolom, hogy egy char-ra mutató
    //pointer adatként csak char-t kaphasson.).Olyan, mint az ages és az i egy adattípusba gyúrva. A C tudja, hogy a pointerek
    //hova mutatnak, az adattípusokat, amikre mutatnak, a típusok méretét és hogy hogyan kell elérhetővé tenni azt az adatot.
    //Pointereken végezhető műveletek: csökkenteni és növelni őket, kivonni őket egymásból, és összeadni őket. Továbbá az
    //adatokat ki lehet nyerni a mutatott helyekről, bele lehet tenni új adatot a mutatott helyre, és minden tömbművelet
    //érvényes rajtuk.
    //Pointer célja: a memória blokkjainak kézzel való elérése, indexelése akkor, amikor a tömbbel ez nem lehetséges (ugye a pointernek van egy neve, és elég a programban csak azt használni, nem kell indexekkel odalépegetni). Szinte minden más esetben tömböket akarunk használni. De vannak olyan esetek, amikor puszta memóriablokkokkal kell dolgozni, akkor jön be a pointer a képbe. A pointer nyers, egyenes hozzáférést ad a memória egy blokkjához, hogy lehessen vele dolgozni.
    /*
     * Egy C kódban 4 nagyon fontos dolgot lehet a pointerekkel csinálni:
     * - Az OS-től elkérni egy memóriadarabot, és dolgozni vele. Ez magában foglalja a stringeket és a structokat.
     * - Függvényparaméterben átadni nagy memóriablokkokat (pl structok) pointerrel, és nem kell az egész dolgot átadni.
     * - Függvénypointer a dinamikus visszahívásra.
     * - Összetett átfésülése a memóradaraboknak, pl. hálózati socketről átfordítani a byte-okat adatstruktúrákra vagy
     *   filedarabolásra.
     *
     * Minden más esetben tömböt érdemes használni. (Régi C kódokban még teljesítménynövelés céljából használtak pointereket
     * tömbök helyett, de ma már mindkettő elérése ugyanarra a gépi kódra fordul és ugyanúgy vannak optimalizálva.)
     *
     * A pointerek nem azonosak a tömbökkel! Pl. ha egy tömb méretét akarjuk megtudni, akkor a sizeof(tömb_neve) a helyes, nem
     * sizeof(ptr), ahola  ptr a tömbre állított pointer.
     * */

int main(int argc, char* argv [])
{
    // az ages egy cím a számítógép számára, amely megegyezik az ages[0]-val. A compiler a nevet mindenhol helyettesíti a
    // címmel, ami nem más, mint a memóriában az a cím, ahol a tömb kezdődik.
    int ages[] = {23, 43, 12, 89, 2};
    char* names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"};

    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    //1. módszer: a tömbök elemeit elkérjük az iterálás során
    for(i = 0; i < count; i++)
    {
        printf("%s has %d years alive. \n",
                names[i], ages[i]);
    }
    printf("---\n");

    printf("Fordított ciklus\n");
    for(i = count - 1; i >= 0; i--)
    {
        printf("%s has %d years alive. \n",
                names[i], ages[i]);
    }
    
    
    printf("---\n");

    //2. módszer: pointereket állítunk a tömbökre, ami ugye meg fog egyezni a tömbök pointerével (a nevével), és a pointeren
    //keresztül kérjük el a mutatott helyek értékeit. A for ciklus fejében sima indexes megoldás, a törzsben a pointert léptetjük, és annak értékét kérjül el. 

    int* p_ages = ages;
    char** p_names = names;

    for(i = 0; i < count; i++)
    {
        
        printf("%s has %d years alive. \n",
              *(p_names+i), *(p_ages+i));
    }


    printf("---\n");

    printf("Fordított sorrendben:\n");


    for(i = count - 1; i > 0; i--)
    {
        
        printf("%s has %d years alive. \n",
              *(p_names+i), *(p_ages+i));
    }


    printf("---\n");
    
    //3. módszer: a létrehozott pointereken keresztül kérjük el az elemeket (mint az 1-esnél). Nyilván ugyanaz, mivel
    //ráirányítottuk a pointert a tömbökre, és ha lépkedünk velük, az ugyanaz, mintha az eredeti címet növelnénk.

    
    for(i = 0; i < count; i++)
    {
        
        printf("%s has %d years alive. \n",
            p_names[i], p_ages[i]);
    }

    printf("---\n");
    printf("Fordított sorrendben:\n");


    for(i = count - 1; i > 0; i--)
    {
        
        printf("%s has %d years alive. \n",
            p_names[i], p_ages[i]);
    }

    printf("---\n");

    //4.módszer: A 2. módszer másképp: itt a "logika" a ciklus fejében van.A for ciklus fejében a ráirányított és az eredeti címekkel dolgozunk úgy, hogy a törzsben már csak a pointer értékét kelljen elkérni. Index itt nincs.
    for(p_names = names, p_ages = ages; (p_names - names) < count; p_names++, p_ages++) 
    {
        
        printf("%s has %d years alive. \n",
               *p_names, *p_ages);
    }
    printf("---\n");

    printf("Fordított sorrendben:\n");

    for(p_names = names+count-1, p_ages = ages+count-1; (p_names - names) >= 0; p_names--, p_ages--) 
    {
        
        printf("%s has %d years alive. \n",
               *p_names, *p_ages);
    }


    return 0;
}
