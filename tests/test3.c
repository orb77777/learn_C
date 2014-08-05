#include<stdio.h>
#include <math.h>

int main()
{
    //char *p;
    //p = "hello";
    //*(p+2) = 'x';

    //printf("%s\n",p);
    //printf("%x\n",&p);
    //printf("%s\n",*&p);
    //printf("%x\n",&*&p);
    //printf("%s\n",*&*&p);
    
    printf("%f\n", log(36.0));


    int a[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    printf("%u, %u, %u \n", a[0]+1, *(a[0]+1, ));
    return 0;
}
