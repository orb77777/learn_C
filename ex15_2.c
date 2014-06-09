#include <stdio.h> 

void print_content_with_pointers(int* ages, char** names, int count)
{
    int i = 0;

    //1. módszer: a tömbök elemeit elkérjük az iterálás során
    while(i < count)
    {
        printf("%s has %d years alive. \n",
                *(names+i), *(ages+i));
        i++;
    }
    printf("---\n");

    printf("Fordított ciklus\n");
    for(i = count - 1; i >= 0; i--)
    {
        printf("%s has %d years alive. \n",
                *(names+i), *(ages+i));
    }
    
    
    printf("---\n");
    
}
void print_content_with_addresses(int* ages, char** names, int count)
{
    int i = 0;

    for(i = 0; i < count; i++)
    {
        
        printf("%s has %d years alive. \n",
              names[i], ages[i]);
    }


    printf("---\n");

    printf("Fordított sorrendben:\n");


    for(i = count - 1; i > 0; i--)
    {
        
        printf("%s has %d years alive. \n",
              names[i], ages[i]);
    }


    printf("---\n");
}

int main(int argc, char* argv [])
{
    int ages[] = {23, 43, 12, 89, 2};
    char* names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"};

    int* p_ages = ages;
    printf("Pointer erre a címre mutat: %p \n", p_ages);
    printf("Az ages tömb harmadik eleme: %d \n", *(p_ages+2));
    char** p_names = names;
    printf("p_names pointer erre a címre mutat: %p \n", p_names);
    printf("Az names tömb harmadik elemének 2. betűje: %c \n", *(*(p_names+2)+1));
    //Az alábbi sorban ugye a pointerrel rámutatunk a Mary elemre, ami maga az oda vándoroltatott pointer értéke, majd ehhez még
    //1-et hozzáadunk, ami a Mary első karaktere. Így a Mary-t M nélkül írja ki, mert nem az elejéről kezdi olvasni a stringet(a
    //karaktertömböt), hanem az 1. indextől.
    printf("Az names tömb harmadik elemének lehagyom az első betűjét %s \n", *(p_names+2)+1);

    int count = sizeof(ages) / sizeof(int);
    print_content_with_pointers(p_ages, p_names, count);
    int i = 0;

    print_content_with_addresses(ages, names, count);

    //4.módszer: A 2. módszer másképp: itt a "logika" a ciklus fejében van.A for ciklus fejében a ráirányított és az eredeti címekkel dolgozunk úgy, hogy a törzsben már csak a pointer értékét kelljen elkérni. Index itt nincs.
    for(i = 0; i < count; i++) 
    {
        
        printf("%s has %d years alive. \n",
               p_names[i], p_ages[i]);
    }
    printf("---\n");

    printf("Fordított sorrendben:\n");

    for(i = count - 1; i  >= 0; i--) 
    {
        
        printf("%s has %d years alive. \n",
               p_names[i], p_ages[i]);
    }


    return 0;
}
