#ifndef _ex19_h
#define _ex19_h

// a buildhez kell, csak ekkor látja!!!
#include "object.h"

typedef struct{
    Object proto;
    int hit_points;
} Monster;

void* Monster_move(void* self, Direction direction);
int Monster_attack(void* self, int damage);
int Monster_init(void* self);

struct Room{
    Object proto;
    Monster* bad_guy;
    struct Room* north; 
    struct Room* south;
    struct Room* west; 
    struct Room* east; 
};

//itt azért kell utólag definiálni a típust, mert a struct Room-on belül
//is használom önmagát, és a pointer értékadásoknál (pl. a Map egyik Room*
//ját akarom a struct Room*-mal egyenlővé tenni) warningot ad, hogy ez 
//neki inkompatibilis. Ha azonnal typedef-elnél a Room-ot, akkor a struct
//belső változóiban még nem történik meg a typedef. Legalábbis, úgy 
//gondolom, ez okozza az inkompatibilitást.
typedef struct Room Room;

void* Room_move(void* self, Direction direction);
int Room_attack(void* self, int damage);
int Room_init(void* self);

typedef struct{
    Object proto;
    Room* start;
    Room* location;
} Map;

void* Map_move(void* self, Direction direction);
int Map_attack(void* self, int damage);
int Map_init(void* self);

#endif
