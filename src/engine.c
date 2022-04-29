#include <SDL2/SDL.h>
#include "engine.h"
#include "object.h"
#include "circle.h"
#include "link.h"
#include "time.h"

int mainloop(SDL_Window* window, SDL_Renderer* renderer){
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    SDL_Event event;
    int running = 1;

    Vec2 center = {(double)width/2., (double)height/2.};

    int max_objects = 2500;
    int n_objects = 20;
    int n_links = 19;
    struct Object** all_objects = (struct Object**)malloc(sizeof(struct Object*) * max_objects);
    struct Link** all_links = (struct Link**)malloc(sizeof(struct Link*) * n_links);

    all_objects[0] = NewObject(center.x - center.x/2, center.y, 10, 0);
    for (int i=1; i<n_objects; i++){
        all_objects[i] = NewObject((center.x - center.x/2) + 30*i, center.y, 10, 1);
    }
    all_objects[n_objects-1]->move = 0;

    for (int i=0; i<n_links; i++){
        all_links[i] = NewLink(all_objects[i], all_objects[i+1]);
        // printf("%f, %f, %f, %f\n", all_objects[i]->pos.x, all_objects[i]->pos.y, all_objects[i+1]->pos.x, all_objects[i+1]->pos.y);
    }

    double dt = 0.5;

    int n_subsetps = 5;

    int mousex, mousey, create=0;

    int R = fmin((double)width/2., (double)height/2.) * 9. / 10.;

    uint64 T = get_time(), t;
    uint64 period = 100ULL;

    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    running = 0;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN){
                create = 1;
            }
            else if (event.type == SDL_MOUSEBUTTONUP){
                create = 0;
            }
        }

        t = get_time();
        if ((t-T > period) && create && n_objects < max_objects){
            SDL_GetMouseState(&mousex, &mousey);
            // printf("%d\n", n_objects);
            all_objects[n_objects] = NewObject(mousex, mousey, 9, 1);
            n_objects ++;
            T = t;
        }



//update
        for (int i=0; i<n_subsetps; i++){
            UpdateAll(all_objects, all_links, n_objects, n_links, center, R, dt/n_subsetps);
        }
        // for (int i=0; i<n_objects; i++){
        //     UpdateObject(all_objects[i], center, R, dt);
        // }


//render
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillCircle(renderer, center.x, center.y, R);
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        for (int i=0; i<n_objects; i++){
            if (RenderObject(renderer, all_objects[i])){
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
            }
        }
        SDL_RenderPresent(renderer);
    }

    return 0;
}