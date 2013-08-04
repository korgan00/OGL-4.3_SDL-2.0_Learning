#include <stdio.h>
#include "SDL2/SDL.h"

int mainHW1() {
    //Start SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "No se puede iniciar SDL: %s\n", SDL_GetError());
        return 1;
    }

    //Quit SDL
    SDL_Quit();

    return 0;
}
