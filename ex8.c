#include <stdio.h>

int main(int argc, char* argv[])
{
    int areas[] = {10, 12, 13, 14, 20};
    char name[] = "Andi";
    char full_name[] = {
        'A','n','d','i',
        'B','a','r','t','o','s','\0'
    };

    areas[0] = name[0];
//    areas[0] = 100;
    /* Így felülírhatom az egyik karakterét:
    name[0] = 'h';
*/
    //a sizeof egy operátor, ami megadja byte-ban a méretet, 
    //töbnél nem a pointer méretét adja meg, hanem a tömbét
    printf("The size of an int: %ld\n", sizeof(int));
    printf("The size of areas (int[]): %ld\n",
            sizeof(areas));
    printf("The number of ints in areas: %ld\n",
            sizeof(areas) / sizeof(int));
    printf("The first area is %d, the 2nd %d. \n",
            areas[0], areas[1]);
    
    printf("The size of a char: %ld \n", sizeof(char));
    //Vigyázat! A sizeof a lezáró nullát is beleszámolja a méretbe!
    printf("The size of name (char[]): %ld \n",
            sizeof(name));
    printf("The number of chars: %ld \n",
            sizeof(name) / sizeof(char));
    
    printf("The size of full name (char[]): %ld \n",
            sizeof(full_name));
    printf("The number of chars: %ld \n",
            sizeof(full_name) / sizeof(char));

    printf("name = \"%s\" and full name = \" %s \" \n",
            name, full_name);
    /* Ha nem lenne a full_name-nek lezáró nullája, akkor helyesen csakúgy írná ki, ha megadnánk a printf-nek plusz
     * paramként a full_name méretét.
    printf("name = \"%s\" and full name = \" %.*s \" \n",
            name, sizeof(full_name),full_name);
*/
    return 0;

}
