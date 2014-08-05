#include <stdio.h>

int main()
{
    puts("1. Mi a hiba?");
    
    int a = 5;
    switch(a)
    {
        case 1:
            printf("First");

        case 2:
            printf("Second");

        case 3 + 2:
            printf("Third");

        case 5:
            printf("Final");
            break;

    }



    int i = 2;
    printf("%d %d \n", ++i, i);

    int a = 35;
    printf("%d %d %d %d %d \n", a++, a++, ++a, a++, ++a);
    

    return 0;
}
