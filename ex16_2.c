#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*
 * Stacket használok mindenhol heap helyett (vagyis nincsenek pointerek és malloc)
 * 
 * */

struct Person
{
    char name[30];
    int age;
    int height;
    int weight;
};

struct Person create_Person(char name[30], int age, int height, int weight)
{
    struct Person who; 

    //stringet nem lehet csak úgy =-gel másolni!
    strcpy(who.name, name);
    who.age = age;
    who.height = height;
    who.weight = weight;

    return who;
}


void Person_print(struct Person who)
{
    printf("Name: %s \n", who.name);
    // A \t 1 TAB-ot rak elé.
    printf("\tAge: %d \n", who.age);
    printf("\tHeight: %d \n", who.height);
    printf("\tWeight: %d \n", who.weight);
}

int main(int argc, char* argv[])
{
    struct Person frank = create_Person("Frank Sinatra", 82, 165, 43);

    struct Person joe = create_Person("Joe Szabo", 23, 182, 78);

    printf("Joe is at memory location: %p \n", &joe);
    Person_print(joe);

    printf("Frank is at memory location: %p \n", &frank);
    Person_print(frank);

    frank.age += 20;
    frank.height -= 2;
    frank. weight += 10;
    Person_print(frank);
    
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 10;
    Person_print(joe);


    return 0;
}
