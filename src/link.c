#include <stdlib.h>
#include "vector.h"
#include "link.h"
#include "object.h"

void ApplyLink(struct Link* l){
    struct Object* object1 = l->object1;
    struct Object* object2 = l->object2;
    double d = dist(object1->pos, object2->pos);

    // printf("okay\n");
    Vec2 axis = Vec2SubVec2(object1->pos, object2->pos);
    Vec2 n = Vec2MultScalar(axis, 1/d);
    // printf("%f, %f, %f\n", d, n.x, n.y);
    if (object1->state & 1){
        if (object2->state & 1){
            object1->pos = Vec2AddVec2(object1->pos, Vec2MultScalar(n, (l->len - d)/2));
            object2->pos = Vec2SubVec2(object2->pos, Vec2MultScalar(n, (l->len - d)/2));
        }
        else{
            object1->pos = Vec2AddVec2(object1->pos, Vec2MultScalar(n, (l->len - d)));
        }
    }
    else{
        if (object2->state & 1){
            object2->pos = Vec2SubVec2(object2->pos, Vec2MultScalar(n, (l->len - d)/2));
        }
    }
    // printf("%f, %f\n", object1->pos.x, object1->pos.y);
}

void ApplyLinks(struct Link** all_links, int n_links){
    for (int i=0; i<n_links; i++){
        ApplyLink(all_links[i]);
    }
}

struct Link* NewLink(struct Object* o1, struct Object* o2){
    struct Link* l = (struct Link*)malloc(sizeof(struct Link));
    l->object1 = o1;
    l->object2 = o2;
    l->len = dist(o1->pos, o2->pos);
    return l;
}

void DestroyLink(struct Link* l){
    free(l);
}