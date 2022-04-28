typedef struct{
    double x, y;
} Vec2;

Vec2 NewVec2(double x, double y);
Vec2 Vec2AddVec2(Vec2 a, Vec2 b);
Vec2 Vec2SubVec2(Vec2 a, Vec2 b);
Vec2 Vec2MultScalar(Vec2 a, double b);
double dist(vec2 a, Vec2 b);