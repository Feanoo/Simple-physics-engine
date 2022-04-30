#ifndef _QTREE
#define _QTREE 1

#include "vector.h"
#include "object.h"

extern int QUADTREE_MAX_OBJECTS;

struct Quadtree{
    struct Quadtree* childs[4];
    Vec2 topleft, size;
    struct Object** objects;
    int n_objects;
};

#endif