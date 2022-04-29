#ifndef _LINK
#define _LINK 1

struct Link{
    struct Object* object1;
    struct Object* object2;
    double len;
};
#include "object.h"

void ApplyLink(struct Link* l);
void ApplyLinks(struct Link** all_links, int n_links);

struct Link* NewLink(struct Object* o1, struct Object* o2);
void DestroyLink(struct Link* l);

#endif