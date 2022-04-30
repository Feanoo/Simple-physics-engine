#include "vector.h"
#include "link.h"
#include "object.h"

int mainloop(SDL_Window* window, SDL_Renderer* renderer);
void ApplyConstraint(struct Object* object, Vec2 center, int radius);
void UpdateAll(SDL_Renderer* renderer, struct Object** all_objects, struct Link** all_links, int n_objects, int n_links, Vec2 center, int radius, double dt);
void UpdateObject(struct Object* object, Vec2 center, int radius, double dt);
void UpdateObjectPosition(struct Object* object, double dt);
void Accelerate(struct Object* object, Vec2 acc);
int RenderObject(SDL_Renderer* renderer, struct Object* object);
