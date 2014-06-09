#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    /*Minden fájlművelettel kapcsolatos dolog az stdio.h-ban van.
     *A FILE adattípus a streamet jelöli a C-ben. FILE*-ként használandó, mert az input/output könyvtárfüggvények foglalják le és tartják karban a FILE objektumokat, ezért érdemes pointert tartani rá, mint hogy magunk foglalkozzunk azzal, ami belül meg van már valósítva.
     *
     * FILE* fopen(const char* filename, const char* opentype) -> megnyit egy streamet a fájl (filename) I/O-jához, és visszaad
     * egy pointert erre a streamre. Az opentype-pal adjuk meg neki, hogy mire nyissuk meg a fájlt:
     * 'r' olvasásra nyitja meg a fájlt, aminek már léteznie kell előtte!
     * 'w' írásra nyitja meg a fájlt, nem kell léteznie, ekkor létrehozza. Ha már létezik, felülírja a tartalmát!
     * 'a' hozzáfűzéshez nyitja meg, tehát a file végére fog írni. Ha nem létezik a fájl, létrehozza.
     * 'r+' olvasásra ÉS írásra,  léteznie kell a fájlnak, és az elejétől elkezdi átírni (ha több szöveg volt benne, akkor az
     *      elejétől felülír annyit, amennyit megadunk, de a többi cucc ott marad!)
     * 'w+' olvasásra és írásra, nem kell léteznie a fájlnak, és felülírja
     * 'a+' olvasásra és hozzáfűzésre nyitja meg ill. hozza létre a fájlt. Az olvasás az elejétől történik, de a hozzáfűzés a
     *      végétől.
     *  A '+'-osoknak tehát olyan stream kell, ami inputot és outputot is csinál. Ilyenkor kötelező használni az fflush(..)-t,
     *  hogy mikor váltunk a két mód között, azelőtt a belső bufferek megfelelően kiürüljenek.*/
   FILE* file = fopen("file.txt", "w+");

    char text[] = "hah";
    printf("A text mérete: %lu \n", sizeof(text));
    /*
     *size_t fwrite(const void* data, size_t size, size_t count, FILE* stream)->
     *  size*count -nyi adatot másol a data tömbból. a streamre. Siker esetén a count-ot adja vissza.
     * */
    fwrite(text, sizeof(text), 2, file);

    /*
     * Csak tesztre, hogy meg tudjam szakítani a program futását CTRL+C-vel. Ekkor ugyanis nem jut el a flushig, de a program
     * nem is exit-tel lép ki, különben lenne automatikus flush (biztos abort()-ot hív ilyenkor). A lényeg, hogy így nem kerül
     * bele az adat a fájlba. A sleep az unistd.h-ban van.*/
    sleep(5);

    /*
     * int fflush(FILE* stream) ->
     *      a streamen az adatok egy output bufferbe (összefüggő virtuális memóriaterület) kerülnek, és flush hívásakor azt
     *      akarjuk, hogy a híváskor a buffer tartalma kerüljön bele az fopen()-nél megadott fájlba.
     *
     *A flush alapból megtörténik, ha:
     *     - ki akarok írni valamit (do output), és az output buffer tele van
     *     - a stream bezárásakor (fclose)
     *     - amikor a program exit()-tel kilép (a main is így lép ki).
     *     - ha a stream sorokat pufferel, akkor minden új sornál
     *     - amikor egy input művelet bármelyik(!) streamen kiolvassa az adatot a file-jából.
     *      
     *Tehát akkor kell fflush()-o hívni, ha ezektől eltérő esetekben / időpontokban  szeretnénk flush-olni.
     *      ?Azért van rá szükség, mert a file-ba írás egy költséges művelet (háttértár), és így lehet
     *      hatékonnyá tenni.*/
    fflush(file);

    /*
     * int fclose(FILE* stream) ->
     *      lezárja a streamet, és megszakítja a kapcsolatot a streamhez tartozó file-lal. Ekkor minden pufferelt outputot
     *      beleír a fájlba, és minden pufferelt inputot töröl. Siker esetén 0-val tér vissza, egyébként EOF-fal. Fontos a
     *      hívása után ellenőrizni, hogy renben bezárult-e, mert ilyenkor sok hiba elő szokott jönni. Pl. az output buffer-t
     *      ki akarja írni a file-ba mielőtt bezárná, de a háttértár megtelt. */
    fclose(file);


    return 0;
}
