#include "circle.h"
#include "object.h"

#define GRAVITY NewVec2(0.0, 1.0)

int RenderObject(SDL_Renderer* renderer, struct Object* object){
    return SDL_RenderFillCircle(renderer, object->pos.x, object->pos.y, object->radius);
}

void UpdateObject(struct Object* object, double dt){

    Accelerate(object, GRAVITY);
    UpdateObjectPosition(object, dt);
}

void UpdateObjectPosition(struct Object* object, double dt){
    Vec2 velocity = Vec2SubVec2(object->pos, object->old_pos);
    object->old_pos = object->pos;

    object->pos = Vec2AddVec2(object->pos, Vec2AddVec2(velocity, Vec2MultScalar(object->acceleration, dt*dt)));
    object->acceleration.x = 0.;
    object->acceleration.y = 0.;
}

void Accelerate(struct Object* object, Vec2 acc){
    object->acceleration = Vec2AddVec2(object->acceleration, acc);
}

int CheckCollision(struct Object* object1, struct object2){
    return dist(object1->pos, object2->pos) < object1->radius + object2->radius;
}

void CollideObjects(struct Object* object1, struct Object* object2){
    if (CheckCollision(object1, object2)){
        object1->pos = object1->old_pos;
        object2->pos = object2->old_pos;
    }
}

struct Object* NewObject(double x, double y, int radius){
    struct Object* o = (struct Object*)malloc(sizeof(struct Object));
    Vec2 p = {x, y};
    Vec2 op = {x, y};
    Vec2 a = {0., 0.};

    o->pos = p;
    o->old_pos = op;
    o->acceleration = a;
    o->radius = radius;

    return o;
}

void DestroyObject(struct Object* object){
    free(object);
}