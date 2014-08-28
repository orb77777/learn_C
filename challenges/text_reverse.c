#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
    //így a text nem read-only, ha char* text-ként deklarálom, akkor az const lesz, és read-only
    char text[] = "Na engem fordits meg";

    char* letter = text;
    int number_of_words = 1;
    int i;
    for(i = 0; *letter != '\0'; i++, letter++)
    {
        if(*letter == ' ')
        {
            number_of_words++;
        }

    }

    printf("Number of words: %d \n", number_of_words);

    char* words[number_of_words];
    int j;
    words[0] = text;
    //nagyon oda kell figyelni, hogy a letter pointert itt megint az elejére állitsam, mert az előző ciklus elállitgatta!!!
    letter = text;
    for(i = 0, j = 1; *letter != '\0'; i++,letter++)
    {
        if(*letter == ' ')
        {
            words[j] = letter+1;
            j++;
        }

    }

    for(i = 0; i < number_of_words; i++)
    {
        printf("%c \n", *words[i]);
    }

    char* reversed_text = malloc(strlen(text) + 1);
    if(!reversed_text)
    {
        exit(3);
    }


    char* k; 
    int last_index;
    j = 0;
    for(i = number_of_words - 1; i >= 0; i--)
    {
        char* start = words[i];
        char* end;
        if(i == number_of_words - 1)
        {
            last_index = strlen(text);
            end = text+last_index;
        }
        else
        {
            end = words[i+1];
        }

        for(k = start; k < end && j < strlen(text); k++, j++)
        {
            reversed_text[j] = *k; 
        }

    }

    reversed_text[last_index] = '\0';


    for(i = 0; i < last_index; i++)
    {
        printf("%s \n", reversed_text);
    }

    free(reversed_text);
    return 0;
}
