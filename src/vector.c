#include <math.h>
#include "vector.h"

Vec2 NewVec2(double x, double y){
    Vec2 c = {x, y};
    return c;
}

Vec2 Vec2AddVec2(Vec2 a, Vec2 b){
    Vec2 c = {a.x + b.x, a.y + b.y};
    return c;
}

Vec2 Vec2SubVec2(Vec2 a, Vec2 b){
    Vec2 c = {a.x - b.x, a.y - b.y};
    return c;
}

Vec2 Vec2MultScalar(Vec2 a, double b){
    Vec2 c = {a.x * b, a.y * b};
    return c;
}

double dist(vec2 a, Vec2 b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}