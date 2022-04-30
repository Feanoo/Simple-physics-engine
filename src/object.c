#include "circle.h"
#include "object.h"
#include "link.h"


int RenderObject(SDL_Renderer* renderer, struct Object* object){
    return SDL_RenderDrawCircle(renderer, object->pos.x, object->pos.y, object->radius);
}

struct Object* NewObject(double x, double y, int radius, int m){
    struct Object* o = (struct Object*)malloc(sizeof(struct Object));
    Vec2 p = {x, y};
    Vec2 op = {x, y};
    Vec2 a = {0., 0.};

    o->pos = p;
    o->old_pos = op;
    o->acceleration = a;
    o->radius = radius;
    o->move = m;

    return o;
}

void DestroyObject(struct Object* object){
    free(object);
}