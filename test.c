#include <stdio.h>

int main()
{
    printf("1. feladat: Mit ír ki? \n");
    int i = 0, x = 10, y = 100 % 90;
    for(i = 1; i < 10; i++)
    if(x != y);
        printf("haha \n");


    printf("2. feladat: Mit ír ki? \n");
    int k, num = 30;
    k = (num > 5 ? (num <= 10 ? 100 : 200) : 500);
    printf("%d \n", num);


    printf("3. feladat: Mi a hiba? \n");
    
    struct emp
    {
        char name[20];
        float sal;
    };

    struct emp e[10];
    //int i;
    for(i = 0; i <= 9; i++)
        scanf("%s %f", e[i].name, &e[i].sal);


    return 0;
}
