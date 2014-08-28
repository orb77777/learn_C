#include <stdio.h>

void test_pointer_aliasing(int* x, int* y)
{
    if(x != y)
    {
        *x ^= *y;
        *y ^= *x;
        *x ^= *y;
    }
}
/*
 * A C a tömbön nem végez ellenőrzést, hogy a méretét ne lépjem túl, és mivel indexelés nem létezik, ezért a 
 * pointerrel, ami a tömb neve ugyebár, csak lépkedek arrébb, ha túlmentem, akkor azon a memóriaterületen levő
 * adatot adja vissza. DURVA! 
 * De ami ennél is durvább az az, hogy a stack-en létrehozott változók (itt most tömb, és egy int) a memóriában egymás után
 * következhetnek, és ezért ha tovább írom a tömböt, akkor felülírom a köv memóriaterületen levő adatot. Ebben az
 * implementációban (gcc) van egy kis hely hagyva a kettő között, így 1-gyel kiindexelve még nem írom át, de a következővel már
 * átírom. Ez az átlapolódás. 
 *  a C standard nem   határozza  meg, hogy a változókat hogyan kell a memóriában elhelyezni.
 * */
int main(int argc, char* argv[])
{
    int array[2] = {1,2};
    int number = 3;

    //ha tovább írom a tömböt 1 számmal, akkor az még nem írja felül a number-t, de ha már kettővel írom túl, akkor igen
    array[2] = 20;
    array[3] = 100;

    printf("A tomb elso eleme: %d \n", array[0]);
    printf("A tomb masodik eleme: %d \n", array[1]);
    printf("A tomb harmadik eleme: %d \n", array[2]);
    printf("A tomb negyedik eleme: %d \n", array[3]);
    printf("A szam: %d \n", number);

    int a = 5;
    int* x = &a;
    //*x = 5;
    //int* y = x;
    a = 10;
    int* y = &a;
    test_pointer_aliasing(x, y);

    printf("x: %d, y:%d \n", *x, *y);
    

    return 0;
}
