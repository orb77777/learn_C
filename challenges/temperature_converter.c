#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int lower_limit;
    int higher_limit;
    int step;

    const int expected_lower_limit = 0;
    const int expected_higher_limit_min = 10;
    const int expected_higher_limit_max = 50000;
    const int expected_step_min = 0;
    const int expected_step_max = 10;

    printf("Please give in a lower limit, limit >= 0: ");
    scanf("%d", &lower_limit);

    if(lower_limit < expected_lower_limit)
    {
        printf("Lower limit can't be lower than zero! \n");
        exit(1);
    }

    printf("Please give in a higher limit, 10 > limit <= 50000: ");
    scanf("%d", &higher_limit);

    if(higher_limit < expected_higher_limit_min || higher_limit > expected_higher_limit_max)
    {
        printf("10 > higher limit <= 50000 \n");
        exit(2);
    }

    printf("Please give in a step, 0 < step <= 10: ");
    scanf("%d", &step);

    if(step < expected_step_min  || step > expected_step_max)
    {
        printf("Invalid step size. \n");
        exit(3);
    }

    int difference = higher_limit - lower_limit;
    if(difference < step)
    {
        printf("ERROR: you gave in larger step than the scale. \n");
        exit(4);
    }

    float celsius;
    int i;
    float fahrenheit;
    printf("Celsius                Fahrenheit \n");
    printf("-------                ----------- \n");
    for(i = lower_limit; i <= higher_limit; i += step)
    {
        celsius = i;
        fahrenheit = 1.8 * celsius + 32;
        printf("%0.10f               %0.10f \n", celsius, fahrenheit);

    }

    return 0;
}
