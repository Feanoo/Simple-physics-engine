#include "circle.h"
#include "object.h"
#include "link.h"

#define GRAVITY NewVec2(0.0, 1.0)
#define G 6.6

int RenderObject(SDL_Renderer* renderer, struct Object* object){
    return SDL_RenderDrawCircle(renderer, object->pos.x, object->pos.y, object->radius);
}

void UpdateObject(struct Object* object, Vec2 center, int radius, double dt){
    if (object->state & 2){
        ApplyGravity(object);
    }
    ApplyConstraint(object, center, radius);
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

void ApplyGravity(struct Object* object){
    Accelerate(object, GRAVITY);
}

void ApplyConstraint(struct Object* object, Vec2 center, int radius){
    double d = dist(object->pos, center);
    if (d > radius - object->radius){
        Vec2 n = Vec2MultScalar(Vec2SubVec2(object->pos, center), 1/d);
        object->pos = Vec2SubVec2(object->pos, Vec2MultScalar(n, (d + object->radius - radius)));
    }
}

int CheckCollision(struct Object* object1, struct Object* object2){
    return dist(object1->pos, object2->pos) < object1->radius + object2->radius;
}

void CollideObjects(struct Object* object1, struct Object* object2){
    double d = dist(object1->pos, object2->pos);

    if (d < (object1->radius + object2->radius)){
        // printf("okay\n");
        Vec2 n = Vec2MultScalar(Vec2SubVec2(object1->pos, object2->pos), 1/d);
        // printf("%f, %f, %f\n", d, n.x, n.y);
        if (object1->state & 1){
            object1->pos = Vec2AddVec2(object1->pos, Vec2MultScalar(n, (object2->radius + object1->radius - d)/2));
        }
        if (object2->state & 1){
            object2->pos = Vec2SubVec2(object2->pos, Vec2MultScalar(n, (object2->radius + object1->radius - d)/2));
        }
        // printf("%f, %f\n", object1->pos.x, object1->pos.y);
    }
}

void ApplyNewtonianGravity(struct Object* object1, struct Object* object2){
    double d = dist(object1->pos, object2->pos);
    double f = G * (object1->mass * object2->mass) / d;

    Vec2 n = Vec2MultScalar(Vec2SubVec2(object1->pos, object2->pos), 1/d);

    Accelerate(object1, Vec2MultScalar(n, -f/object1->mass));
    Accelerate(object2, Vec2MultScalar(n, f/object2->mass));
}

void UpdateAll(struct Object** all_objects, struct Link** all_links, int n_objects, int n_links, Vec2 center, int radius, double dt){
    ApplyLinks(all_links, n_links);
    for (int i=0; i<n_objects; i++){
        for (int j=i+1; j<n_objects; j++){
            CollideObjects(all_objects[i], all_objects[j]);
            ApplyNewtonianGravity(all_objects[i], all_objects[j]);
        }
        if (all_objects[i]->state & 1){
            UpdateObject(all_objects[i], center, radius, dt);
        }
    }
}

struct Object* NewObject(double x, double y, int radius, double mass, int state){
    struct Object* o = (struct Object*)malloc(sizeof(struct Object));
    Vec2 p = {x, y};
    Vec2 op = {x, y};
    Vec2 a = {0., 0.};

    o->pos = p;
    o->old_pos = op;
    o->acceleration = a;
    o->radius = radius;
    o->mass = mass;
    o->state = state;

    return o;
}

void DestroyObject(struct Object* object){
    free(object);
}