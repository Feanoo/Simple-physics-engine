#ifndef _OBJ
#define _OBJ 1

#include <SDL2/SDL.h>
#include "vector.h"
#include "link.h"

struct Object{
    Vec2 pos, old_pos, acceleration;
    int radius;
    int state;
    double mass;
};

void UpdateObject(struct Object* object, Vec2 center, int radius, double dt);
void UpdateObjectPosition(struct Object* object, double dt);
void Accelerate(struct Object* object, Vec2 acc);
int RenderObject(SDL_Renderer* renderer, struct Object* object);
struct Object* NewObject(double x, double y, int radius, double mass, int state);
void DestroyObject(struct Object* object);
void ApplyConstraint(struct Object* object, Vec2 center, int radius);
void ApplyGravity(struct Object* object);
void UpdateAll(struct Object** all_objects, struct Link** all_links, int n_objects, int n_links, Vec2 center, int radius, double dt);
#endif