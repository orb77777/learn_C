#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// A struktúra egy összetett típus (compound data type), ami egy memóriablokkban tárolódik, de minden változóját külön-külön el
// lehet érni a nevére való hivatkozással (mint egy DB rekord, vagy egy OO osztály).
// A logikai előnye mellett fizikai előnye is van, mert nem kell foglalkozni azzal, hogy ilyen egy csomagba zárásnak mekkora
// memóriaméret kell, hova kell tenni stb. 
struct Person
{
    char* name;
    int age;
    int height;
    int weight;
};

struct Person* create_Person(char* name, int age, int height, int weight)
{
    // A malloc-kal foglalok le a paraméterében megadott méretű nyers memóriablokkot. Void*-t ad vissza, amit át kellene
    // castolni a lefoglalt területen tárolt adat típusára, de = -nél ez elhagyható (kivéve régi C-ben).
    struct Person* who = malloc(sizeof(struct Person));

    //Ez egy makró. "állítsd azt, hogy nem NULL a malloc által visszaadott pointer" 
    //"Verify the programmer's belief that expression is nonzero at this point in the program." (GNU doc)
    //Ha nulla a feltételben kapott érték, akkor leállítja a program futását, és kíirja a hibaüzenetet: "Assertion 'expression'
    //failed" az stderr-re.
    assert(who != NULL);

    // Az strdup(const char*) malloc-ot hajt végre stringeknél. Lemásolja a paraméterül kapott stringet, dinamikusan foglal egy
    // ekkora területet, és odamásolja az adatot. Visszaad aztán erre a címre egy mutatót.
    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void destroy_Person(struct Person* who)
{
    assert(who != NULL);

    //mivel tulajdonképpen két malloc történt, ezért két felszabadítás is kell.
    free(who->name);
    free(who);
}

void Person_print(struct Person* who)
{
    printf("Name: %s \n", who->name);
    // A \t 1 TAB-ot rak elé.
    printf("\tAge: %d \n", who->age);
    printf("\tHeight: %d \n", who->height);
    printf("\tWeight: %d \n", who->weight);
}

int main(int argc, char* argv[])
{
    struct Person* frank = create_Person("Frank Sinatra", 82, 165, 43);
    struct Person* joe = create_Person("Joe Szabo", 23, 182, 78);

    printf("Joe is at memory location: %p \n", joe);
    Person_print(joe);

    printf("Frank is at memory location: %p \n", frank);
    Person_print(frank);

    frank->age += 20;
    frank->height -= 2;
    frank-> weight += 10;
    Person_print(frank);
    
    joe->age += 20;
    joe->height -= 2;
    joe-> weight += 10;
    Person_print(joe);

    destroy_Person(frank);
    destroy_Person(joe);

    return 0;
}
