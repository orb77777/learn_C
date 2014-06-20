#include <stdio.h>
#include <stdlib.h>
#include "ex19.h"
#include <time.h>

//TODO:felszabadítani a dinamikus memóriafoglalásokat!

int Monster_attack(void* self, int damage)
{
    Monster* monster = self;

    printf("You attack %s! \n", monster->_(description));

    monster->hit_points -= damage;

    if(monster->hit_points > 0)
    {
        printf("It's still alive. \n");
        return 0;
    }
    else
    {
        printf("It is dead! You won. Congratulations! \n");
        exit(1);
    }
}

int Monster_init(void* self)
{
    Monster* monster = self;
    monster->hit_points = 10;
    return 1;
}

Object MonsterProto = {
    .attack = Monster_attack,
    .init = Monster_init
};

void* Room_move(void* self, Direction direction)
{
    Room* location = self;
    Room* next_room = NULL;

    if(direction == NORTH && location->north)
    {
        next_room = location->north;
        printf("You go north, into: \n");
    }
    else if(direction == SOUTH && location->south)
    {
        next_room = location->south;
        printf("You go south, into: \n");
    }
    else if(direction == WEST && location->west)
    {
        next_room = location->west;
        printf("You go west, into: \n");
    }
    else if(direction == EAST && location->east)
    {
        next_room = location->east;
        printf("You go east, into: \n");
    }
    else{
        printf("You can't go that direction.\n");
        //A példakód itt feleslegesen állítja a next_room-ot megint NULL-ra.
    }

    if(next_room)
    {
        next_room->_(describe)(next_room);
    }

    return next_room;
}

int Room_attack(void* self, int damage)
{
    Room* room = self;
    Monster* monster = room->bad_guy;

    if(monster)
    {
        monster->_(attack)(monster, damage);
        return 1;
    }
    else{
        printf("You flail in the air at nothing. Idiot. \n");
        return 0;
    }
}

Object RoomProto = {
    .move = Room_move,
    .attack = Room_attack,
};

int Map_init(void* self)
{
    Map* map = self;

    Room* hall = NEW(Room,"The great hall.");
    Room* throne = NEW(Room,"The throne room");
    Room* arena = NEW(Room,"The arena, with the minotaur");
    Room* kitchen = NEW(Room,"Kitchen, you have knife now");

    arena->bad_guy = NEW(Monster, "The evil minotaur");

    hall->north = throne;
    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->west = throne;
    kitchen->west = throne;

    map->start = hall;
    map->location = hall;

    return 1;
}

void* Map_move(void* self, Direction direction)
{
    Map* map = self;
    Room* location = map->location;
    Room* next_room = NULL;

    next_room = location->_(move)(location, direction);

    if(next_room)
    {
        map->location = next_room;
    }
    return next_room;
}

int Map_attack(void* self, int damage)
{
    Map* map = self;
    Room* location = map->location;

    return location->_(attack)(location, damage);
}
//létrehozok egy Object típusú globális változót, ami szintén egy struct, és inicializálom a változóit.
//Így tudom az Object_new()  2. paraméterében értékül adni annak az Objectnek ezt.Nyilván egy OO n
//nyelvnél ez az örökléssel megoldott, és abból kiindulva ezt egy kicsit nehézkes felfogni, de izgi :)
//
// A fgv. pointereket beállítom a headerben deklarált függvények pointereire, amelyek nem mások,
// mint a fgv.-ek nevei!!!! Alapból minden fgv. neve egy pointer, és ha nem akarom több függvényre
// illeszteni azt a fgv. pointert, akkor nem kell csinálnom neki makrót, elég csak az adott fgv. nevére 
// hivatkozni. Persze, ahhoz, hogy ez működjön, az adott fgv-eket (mint pl. Map_init) ez előtt már
// definiálni kell, mert a deklaráció nem elég (ha csak deklarálva van, hibát dob).
Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};

int process_input(Map* game)
{

    char command = getchar();
    getchar();

    int damage = rand() % 4;

    switch(command)
    {
        //HIBA a példakódban: a -1-et nem eszi meg a getchar()!!
        case 'q':
            printf("Giving up? Don't be coward! Try it again! \n");
            return 0;
            break;
        case 'n':
            game->_(move)(game, NORTH);
            break;
        case 's':
            game->_(move)(game, SOUTH);
            break;
        case 'w':
            game->_(move)(game, WEST);
            break;
        case 'e':
            game->_(move)(game, EAST);
            break;
        case 'a':
            game->_(attack)(game, damage);
            break;
        case 'l':
            printf("You can go: \n");
            if(game->location->north) printf("NORTH --> command: <n> \n");
            if(game->location->south) printf("SOUTH --> command: <s> \n");
            if(game->location->west) printf("WEST --> command: <w> \n");
            if(game->location->east) printf("EAST --> command: <e> \n");
            break;
        default:
            printf("What: %c?\n", command);
    }
    return 1;
}
int main(int argc, char* argv[])
{
    srand(time(NULL));
    printf("\n");
    printf("WELCOME TO THE MINOTAUR KILLING GAME. FIND AND KILL HIM! \n");
    printf("Use one of the following commands:\n");
    printf("<l> --> lists where you can go \n");
    printf("<a> --> attack the Minotaur. \n");
    printf("<q> --> quit the game. Won't be saved \n");
    printf("\n");

    Map* game = NEW(Map,"The Hall of the Minotaur.");
    
    printf("You enter the ");
    game->location->_(describe)(game->location);

    while(process_input(game))
    {

    }

    return 0;
}
