#include <SDL2/SDL.h>
#include "engine.h"
#include "object.h"

int mainloop(SDL_Renderer* renderer){
    SDL_Event event;
    int running = 1;

    int max_objects = 10;
    int n_objects = 1;
    struct Object** all_objects = (struct Object**)malloc(sizeof(struct Object*) * max_objects);
    all_objects[0] = NewObject(400., 300., 30);

    double dt = 0.1;

    int mousex, mousey;

    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = 0;
            }
        }

//update
        for (int i=0; i<n_objects; i++){
            UpdateObject(all_objects[i], dt);
        }


//render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        for (int i=0; i<n_objects; i++){
            if (RenderObject(renderer, all_objects[i])){
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
            }
            else is (event.type == SDL_MOUSEBUTTONDOWN){
                if (n_objects < max_objects){
                    SDL_GetMouseState(&mousex, &mousey);
                    n_objects ++;
                    all_objects[n_objects] = NewObject((double)mousex, (double)mousey, 30);
                }
            }
        }
        SDL_RenderPresent(renderer);
    }

    return 0;
}