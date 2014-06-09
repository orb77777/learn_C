#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>

//forward declaration
//Azokat a függvényeket kell előre deklarálni, amelyeket a kódban korábbi sorokban használunk, mint hogy az definiálva lenne.
//Esetünkben a print_arguments()-et nem kell, mert az az első definiált függvény, tehát előtte nincs rá hivatkozás.
//Az előre deklarált függvények adják a fgv. prototípusát. Miután a fordító feldolgozta a sorokat, amikben ezek vannak, azután
//megengedi, hogy a későbbi sorokban hivatkozás legyen rájuk. Ezen fgv.-ek definíciója lehet később ugyanebben a fájlban vagy
//egy másikban. A linker feladata, hogy az egyes függvények referenciáit összekösse az egy vagy több object file-ban a
//definíciójukkal, aminek ugye egyedinek kell lennie.
//TESZT:kivenni az egyik elődeklarációt!
int can_print_it(wchar_t);
void print_letters(int, wchar_t arg[]);

void print_arguments(int argc, char* argv[])
{
    int i = 0;
    for(i = 1; i < argc; i++)
    {
        // A "size_t strlen(const char* s)" visszaadja a string hosszát a lezáró nulla nélkül.
        int length = strlen(argv[i]);
        printf("Az argumentum string hossza: %d \n", length);
        print_letters(length, argv[i]);
    }
}

void print_letters(int length, wchar_t arg[])
{
    int i = 0;
    for(i = 0; i < length; i++)
    {
//        printf("Egy karakter: %ls \n", arg[i]);
        if(can_print_it(arg[i]))
        {
            printf("'%c' == %d \n", arg[i], arg[i]);
        }
    }
}

int can_print_it(wchar_t ch)
{
    //az isblank igazat ad (0-tól eltérőt), ha a paramétere SPACE vagy TAB. Eredetileg egy GNU kiegészítés volt, de a C99
    //szabványnak már része.
    //A logikai operátorok a 0-tól különböző értéket igaznak tekintik (lehet az 2-es vagy 3-as is stb.). A matekban ez nincs
    //így.
    return isalpha(ch) || isblank(ch);
}

//static wchar_t* char_to_wchar(const char* text)
//{
//}

int main(int argc, char* argv[])
{
    size_t size_of_text = strlen(argv[1]) + 1;
    wchar_t* wide_array[100];
    int len = mbstowcs(wide_array[0], argv[1],size_of_text);
    //wchar_t* wide_strings = char_to_wchar(argv); 
    //wcscat(wide_array[0], L" (wchar_t *)");
    printf("Ennyit alakított át: %d \n", len);
    //printf("%ls \n", wide_array[0]);
    //print_arguments(argc, argv);
    return 0;
}
