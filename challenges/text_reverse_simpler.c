#include <stdio.h>
#include <string.h>

/*
 * FELADAT: a split() fgv megírása, és egy kapott konstans sztring szavait visszaadni fordított sorrendben.
 * */

/*
 * ALAPÖTLET: a space-eket (vagy más határolókat) '\0'-val helyettesítettem,majd amennyi szó van, annyi pointert
 * ráállítok a szavak elejére, ezeket egy tömbben tárolom. Valójában egy char[]-ből csinálok egy char* []-öt.
 * A kiolvasásnál így nem kell külön a karakterekre állítgatni pointereket, mint az előző megoldásomban,
 * hanem csak az adott pointer által mutatott karakternél elkezdeni, és ő a '\0' miatt tudja, hogy meddig 
 * tart a string. A %s miatt a printf eleve eddig olvassa.
 * */
int main(int argc, char* argv[])
{
    const char* text = "Na engem fordits meg";

    //lemásolom egy tömbbe, hogy módosítható legyen
    int text_length = strlen(text) + 1;
    char text_temp[text_length];

    strncpy(text_temp, text, text_length);

    //megszámolom a szavakat
    int i;
    int word_count = 1;

    //ÖTLET: számításigény lecserélése memóriaterületre VAGYIS hogy ne kelljen még egyszer végig olvasni
    //a stringet, hogy megtudjam hány szóból áll, felülről megbecsülöm a szavak számát, és annyit
    //foglalok le. Felső becslés számítása: legrövidebb szó 1 betűből áll, és ha páros darab van, akkor a szavak
    //száma a betűk számának a fele, ha páratlan, akkor +1.
    int max_words = text_length/2 + 1;
    char* words[max_words];
    int j;
    // az első szót be kell állítani
    words[0] = text_temp;

    for(i = 0, j =1; i < text_length; i++)
    {
        if(text_temp[i] == ' ')
        {
            words[j] = (text_temp+i+1);
            j++;

            text_temp[i] = '\0';
            word_count++;
        }
    }

    // és akkor csak fordítva kiolvasom
    for(i = word_count - 1; i >= 0; i--)
    {
        printf("%s \n",words[i]);
    }

    return 0;
}

