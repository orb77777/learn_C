#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        puts("ERROR: You need one argument.");
        return 1;
    }
    
    int i = 0;
    for(; argv[1][i] != '\0'; i++)
    {
        switch(argv[1][i])
        {
            //ha nem case-en vagy default-on belül van a kódrészlet, akkor nem veszi figyelembe a switchen belül.
            int j = 15;
            //printf("%d \n", j);
            
            // A case-ben bármi lehet, ami integerré értékelődik: int konstans, char konstans, enum konstans, sizeof() kif.,
            // float konstans.
            case 'a':
            case 'A':
                printf("%d: 'A'\n", i);
            printf("%d \n", j); // hiába inicializáltam a switch elején a j-t, csak a case-eket futtatja le. Pontosabban úgy működik, hogy a switchen belül nem sorrendben hajtja végre az utasításokat. A case-eket a compiler lefordította helyekké, ahova a program ugrik, ha arra értékelődik ki a switch feltétele. A switch kezdetét is megjelöli a fordító (pl. Y), és ahhoz adja hozzá a case-ekhez rendelt helyeket (pl. Y+'A').Nyilván ezek a helyek számokként értékelődnek ki.
                //a break elhagyható, ilynenkor megy tovább a program a feltételek vizsgálásán. Ez pl. olyankor jó, mint itt,
                //hogy 'a' VAGY 'A' esetében mit csináljon.
                break;

            case 'e':
            case 'E':
                printf("%d: 'E'\n", i);
                break;

            case 'i':
            case 'I':
                printf("%d: 'I'\n", i);
                break;

            case 'o':
            case 'O':
                printf("%d: 'O'\n", i);
                break;

            case 'u':
            case 'U':
                printf("%d: 'U'\n", i);
                break;

            case 'y':
            case 'Y':
                //az if blokk jelölésénél hibás a példaprogi
                if(i > 2)
                {
                    printf("%d: 'Y' \n", i);
                    break;
                }
            
            // a default elhagyható, de nem tanácsos, mert akkor nincs lefedve az összes eset
            default:
                printf("%d: %c is not a vowel \n", i, argv[1][i]);

        }
    }
    return 0;
}
