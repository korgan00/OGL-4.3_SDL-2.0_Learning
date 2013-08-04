#include <iostream>
#include "SDL2/SDL.h"

int mainHW3(){
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Window *win = NULL;
    win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == NULL){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *ren = NULL;
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Surface *bmp = NULL;
    bmp = SDL_LoadBMP("Resources/HelloWorlds/hello.bmp");
    if (bmp == NULL){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Texture *tex = NULL;
    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);

    SDL_Delay(2000);

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}
