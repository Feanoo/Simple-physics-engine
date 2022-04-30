#include "quadtree.h"

extern int QUADTREE_MAX_OBJECTS;

void partition(struct Quadtree* tree){
    Vec2 size = Vec2MultScalar(tree->size, 0.5);
    Vec2 pos;
    for (int i=0; i<4; i++){
        pos.x = tree->topleft.x + size.x * (i%2);
        pos.y = tree->topleft.y + size.y * (i>1);
        tree->childs[i] = NewQuadtree(pos, size);
    }

    tree->n_objects = 0;
    int n=0;
    for (int i=0; i<4; i++){
        if (intersect(tree->objects[i], tree->childs[n])){
            if(n){
                tree->objects[tree->n_objects] = tree->objects[i];
                tree->n_objects ++;
                return ;
            }
            n=i;
        }
    }
    AddObjectToTree(tree->objects[n], tree->childs[n]);

    for (int i=tree->n_objects; i<QUADTREE_MAX_OBJECTS; i++){
        tree->objects[i] = NULL;
    }

}


int intersect(struct Object* object, struct Quadtree* tree){ //stolen from https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
    double x, y, w, h;
    x = tree->topleft.x;
    y = tree->topleft.y;
    w = tree->size.x;
    h = tree->size.y;

    Vec2 circleDistance;

    circleDistance.x = abs(object->pos.x - x);
    circleDistance.y = abs(object->pos.y - y);

    if (circleDistance.x > (w/2 + object->radius)){
        return 0;
    }
    if (circleDistance.y > (h/2 + object->radius)){
        return 0;
    }

    if (circleDistance.x <= (w/2)){
        return 1;
    } 
    if (circleDistance.y <= (h/2)){
        return 1;
    }

    double cornerDistance_sq = (circleDistance.x - w/2)*(circleDistance.x - w/2) +
                         (circleDistance.y - h/2) * (circleDistance.y - h/2);

    return (cornerDistance_sq <= (object->radius * object->radius));
}

void AddObjectToTree(struct Object* object, struct Quadtree* tree){
    if (tree->n_objects == QUADTREE_MAX_OBJECTS){
        partition(tree);
    }

    if (tree->childs[0] != NULL){
        int n=0;
        for (int i=0; i<4; i++){
            if (intersect(object, tree->childs[n])){
                if(n){
                    tree->objects[tree->n_objects] = object;
                    tree->n_objects ++;
                    return ;
                }
                n=i;
            }
        }

        AddObjectToTree(object, tree->childs[n]);
    }

    else{
        tree->objects[tree->n_objects] = object;
        tree->n_objects ++;
    }
}

struct Quadtree* NewQuadtree(Vec2 topleft, Vec2 size){
    struct Quadtree* tree = (struct Quadtree*)malloc(sizeof(struct Quadtree));

    tree->topleft = topleft;
    tree->size = size;
    tree->childs[0] = NULL;
    tree->n_objects = 0;
    tree->objects = (struct Object*)malloc(sizeof(struct Object) * QUADTREE_MAX_OBJECTS);

    return tree;
}

void DestroyQuadtree(struct Quadtree* tree){
    free(tree->objects);
    free(tree);
}