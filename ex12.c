#include <stdio.h>

int main(int argc, char* argv[])
{
    //azért kell ez a változó, hogy a kód olvashatóbb legyen.
    int number_of_params = argc -1;
    if(number_of_params == 0)
    {
        printf("Nem adtál meg paramétert. \n ");
    }
    else if(number_of_params > 0 && number_of_params < 3)
    {
        int i = 0;
        for(i = 1; i < number_of_params; i++)
        {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Túl sok paramétert adtál meg.\n");
    }
    return 0;
}
