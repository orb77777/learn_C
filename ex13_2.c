#include <stdio.h>
#include <ctype.h>

/*
 * Változat: a nagy betűket lekezelem mielőtt a switchnek adom: kisbetűvé alakítom.
 * */
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        puts("ERROR: You need one argument.");
        return 1;
    }
    
    int i = 0;
    char** args_pointer = argv;
    for(; *(args_pointer[1]+i) != '\0'; i++)
    {
        char letter = tolower(argv[1][i]);
        switch(letter)
        {
            case 'a':
                printf("%d: 'A'\n", i);
                break;

            case 'e':
                printf("%d: 'E'\n", i);
                break;

            case 'i':
                printf("%d: 'I'\n", i);
                break;

            case 'o':
                printf("%d: 'O'\n", i);
                break;

            case 'u':
                printf("%d: 'U'\n", i);
                break;

            case 'y':
                if(i > 2)
                {
                    printf("%d: 'Y' \n", i);
                    break;
                }
            
            default:
                printf("%d: %c is not a vowel \n", i, args_pointer[1][i]);

        }
    }
    return 0;
}
