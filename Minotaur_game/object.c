#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include <string.h>

int Object_init(void* self)
{
    return 1;
}

void Object_destroy(void* self)
{
    Object* object = self;

    if(object)
    {
        if(object->description)
        {
            free(object->description);
        }

        free(object);
    }
}

void* Object_move(void* self, Direction direction)
{
    printf("You can't go that direction. \n");
    return NULL;
}

int Object_attack(void* self, int damage)
{
    printf("You can't attack that. \n");
    return 0;
}

void Object_describe(void* self)
{
    Object* object = self;

    printf("%s \n", object->description);
}
//Miért void*-ot adunk vissza, miért nem Object*-ot?
void* Object_new(size_t size, Object proto, char* description)
{

    if(!proto.init) proto.init = Object_init;
    if(!proto.destroy) proto.destroy = Object_destroy;
    if(!proto.move) proto.move = Object_move;
    if(!proto.attack) proto.attack = Object_attack;
    if(!proto.describe) proto.describe = Object_describe;

    Object* object = calloc(1, size);
    *object = proto;
    
    object->description = strdup(description);

    if(!object->init(object))
    {
        object->destroy(object);

        return NULL;
    }

    return object;
}
