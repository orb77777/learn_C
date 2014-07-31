#include <stdio.h>

int main()
{
    unsigned long long a = 50;
    int i;
    unsigned long long number = 1;
    for(i = 1; i <= a; i++)
    {
        number = number * i;
    }

    printf("%llu \n", number);

    return 0;
}
