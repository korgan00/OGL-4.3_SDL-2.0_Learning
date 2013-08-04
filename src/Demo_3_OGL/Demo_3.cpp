/*
 * Demo_3.cpp
 *
 *  Created on: 01/07/2013
 *      Author: Korgan
 *
 *  Based on:
 *  http://www.sdltutorials.com/sdl-tutorial-basics
 *  http://www.libsdl.org/docs/html/guidebasicsinit.html
 */

#include "Demo_3.h"
#include "GL/gl.h"
#include <iostream>

const char* Demo_3::WIN_TITLE = "Titulo de la Ventana";

Demo_3::Demo_3() : running(false), window(NULL), ctxt(NULL), aux(0){}

void Demo_3::OnEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_KEYUP:
            switch(event->key.keysym.sym){
                case SDLK_KP_PLUS:
                    aux++;
                    aux %= 3;
                    break;
                case SDLK_v:
                    std::cout << glGetString(GL_VERSION) << std::endl;
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
                default:
                    break;
            }
            break;
        case SDL_QUIT:
            running = false;
            break;
        default:
            break;
    }
}
void Demo_3::OnLoop() {}
void Demo_3::OnRender() {

    glClearColor(aux==0? 1:0, aux==1? 1:0, aux==2? 1:0, 1.0);
    glClear( GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}

void Demo_3::OnCleanup() {
    SDL_GL_DeleteContext(ctxt);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Demo_3::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    window = SDL_CreateWindow(WIN_TITLE,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WIN_WIDTH, WIN_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(!window)
        return false;

    setupOpenGl();

    running = true;

    return true;
}

int Demo_3::OnExecute() {
    if (!Init())
        return -1;

    SDL_Event event;

    while (running) {

        while (SDL_PollEvent(&event))
            Event(&event);

        Loop();
        Render();
    }

    Cleanup();

    return 0;
}


void Demo_3::setupOpenGl(){
   //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
   ctxt = SDL_GL_CreateContext(window);

   //vsync ON
   SDL_GL_SetSwapInterval(1);

}












