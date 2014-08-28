#include <stdio.h>
#include <stdlib.h>

/*
 * Feladat: sorban vannak a számok 1-től kezdődően egy piramisba rendezve. 
 * Input: egy tetszőleges pozitív egész szám
 * ELvárt output: a számnak a piramisban levő jobb és bal gyereke.
 * */

int main(int argc, char* argv[])
{
    
    int i = 1;
    int j = 1;
    int number = atoi(argv[1]);

    //A j-vel számolom a szinteket, az i-be pedig beleteszem minden szint legjobboldali számát, a legnagyobbat.
    //Ha a számom kisebb mint ez, akkor azon a szinten van. Ekkor a j tárolja az aktuális szintet.
    while(number >= i)
    {
        j++;
        i = i + j;
    }

    //A trükk: úgy lehet megkapni a bal gyereket, hogy a számhoz az aktuális szint számát adom hozzá, a jobb meg az eggyel
    //arrébbi.
    int left_child = number + j;
    // egyszerűbben: right_child = left_child++;
    int right_child = number + (j+1);

    printf("number: %d left child: %d right child: %d \n", number, left_child, right_child);
    return 0;
}
