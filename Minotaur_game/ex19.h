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

typedef struct{
    Object proto;
    Monster* bad_guy;
    struct Room* north; 
    struct Room* south;
    struct Room* west; 
    struct Room* east; 
} Room;

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
