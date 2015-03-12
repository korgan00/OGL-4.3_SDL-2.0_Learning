/*
 * Demo_1.cpp
 *
 *  Created on: 01/07/2013
 *      Author: Korgan
 *
 *  Based on:
 *  http://www.sdltutorials.com/sdl-tutorial-basics
 *  http://www.libsdl.org/docs/html/guidebasicsinit.html
 */

#include "Demo_1.h"

Demo_1::Demo_1(): mainwindow(0), running(false){}

void Demo_1::OnEvent(SDL_Event* Event) {
    std::cout << "Event" << std::endl;
}
void Demo_1::OnLoop() {
    std::cout << "Looping" << std::endl;
}
void Demo_1::OnRender() {
    std::cout << "Rendering" << std::endl;
}

void Demo_1::OnCleanup() {
    std::cout << "Cleaning" << std::endl;
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
}

bool Demo_1::OnInit() {
    std::cout << "Init!" << std::endl;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    mainwindow = SDL_CreateWindow("Titulo de la Ventana",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WIN_WIDTH, WIN_HEIGHT,
            SDL_WINDOW_SHOWN);
    if(!mainwindow)
        return false;

    running = true;

    return true;
}

int Demo_1::OnExecute() {
    if (!Init())
        return -1;

    int times = 10;
    while (running) {
        //CONTROL DE EVENTOS
        Event(NULL);
        Loop();
        Render();
        times--;
        if(!times)
            running = false;
    }

    SDL_Delay(2000);

    Cleanup();

    return 0;
}

/*
int Demo_1::OnExecute() {
    if (!Init())
        return -1;

    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            OnEvent(&event);
        }

        Loop();
        Render();
    }

    SDL_Delay(2000);

    Cleanup();

    return 0;
}//*/
