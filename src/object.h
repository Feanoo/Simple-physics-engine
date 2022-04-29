#include "vector.h"

struct Object{
    Vec2 pos, old_pos, acceleration;
    int radius;
};

void UpdateObject(struct Object* object, Vec2 center, int radius, double dt);
void UpdateObjectPosition(struct Object* object, double dt);
void Accelerate(struct Object* object, Vec2 acc);
int RenderObject(SDL_Renderer* renderer, struct Object* object);
struct Object* NewObject(double x, double y, int radius);
void DestroyObject(struct Object* object);
void ApplyConstraint(struct Object* object, Vec2 center, int radius);
void UpdateAll(struct Object** all_objects, int n_objects, Vec2 center, int radius, double dt);