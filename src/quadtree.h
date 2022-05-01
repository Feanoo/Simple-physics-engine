#ifndef _QTREE
#define _QTREE 1

#include "vector.h"
#include "object.h"

extern int* QUADTREE_MAX_OBJECTS;

struct Quadtree{
    struct Quadtree* childs[4];
    Vec2 topleft, size;
    struct Object** objects;
    int n_objects;
};

void AddObjectToTree(struct Object* object, struct Quadtree* tree);
struct Quadtree* NewQuadtree(Vec2 topleft, Vec2 size);
void DestroyQuadtree(struct Quadtree* tree);
int intersect(struct Object* object, struct Quadtree* tree); //stolen from https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
int DrawQuadtree(SDL_Renderer* renderer, struct Quadtree* tree);
#endif