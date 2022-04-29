#include <SDL2/SDL.h>
#include "engine.h"
#include "object.h"
#include "circle.h"

int mainloop(SDL_Window* window, SDL_Renderer* renderer){
    int width, height;
    SDL_GetWindowSize(window, &width, &height);

    SDL_Event event;
    int running = 1;

    int max_objects = 5000;
    int n_objects = 0;
    struct Object** all_objects = (struct Object**)malloc(sizeof(struct Object*) * max_objects);
    // all_objects[0] = NewObject(400., 300., 15);

    double dt = 1;

    int n_subsetps = 5;

    int mousex, mousey;

    Vec2 center = {(double)width/2., (double)height/2.};
    int R = fmin((double)width/2., (double)height/2.) * 9. / 10.;

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
            if (n_objects < max_objects){
                SDL_GetMouseState(&mousex, &mousey);
                // printf("%d\n", n_objects);
                all_objects[n_objects] = NewObject((double)mousex, (double)mousey, 5);
                n_objects ++;
            }
        }

//update
        for (int i=0; i<n_subsetps; i++){
            UpdateAll(all_objects, n_objects, center, R, dt/n_subsetps);
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