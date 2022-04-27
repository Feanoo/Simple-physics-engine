#include "vector.h"

struct Object{
    Vec2 pos, old_pos, acceleration;
    int radius;
};

int RenderObject(SDL_Renderer* renderer, struct Object* object);
struct Object* NewObject(double x, double y, int radius);
void DestroyObject(struct Object* object);
