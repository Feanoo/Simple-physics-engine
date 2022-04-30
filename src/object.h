#ifndef _OBJ
#define _OBJ 1

#include <SDL2/SDL.h>
#include "vector.h"
#include "link.h"

struct Object{
    Vec2 pos, old_pos, acceleration;
    int radius;
    int move;
};

struct Object* NewObject(double x, double y, int radius, int m);
void DestroyObject(struct Object* object);
#endif