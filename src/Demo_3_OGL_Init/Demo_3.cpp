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

const char* Demo_3::WIN_TITLE = "Titulo de la Ventana";

Demo_3::Demo_3() : running(false), window(NULL), ctxt(NULL), aux(0){}

void Demo_3::OnEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_KEYUP:
            switch(event->key.keysym.sym){
				case SDLK_KP_PLUS:
				case SDLK_PLUS:
                    aux++;
                    aux %= 8;
                    break;
				case SDLK_KP_MINUS:
				case SDLK_MINUS:
                    aux+=7;
                    aux %= 8;
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

    glClearColor(	(aux & 1) == 1? 1.0f : 0.0f, 
					(aux & 2) == 2? 1.0f : 0.0f, 
					(aux & 4) == 4? 1.0f : 0.0f, 
					1.0f);
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
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
   //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
   ctxt = SDL_GL_CreateContext(window);

   //vsync ON
   SDL_GL_SetSwapInterval(1);


   if (gl3wInit()) {
        std::cerr << "Failed to initialize gl3w." << std::endl;
		return;
    }

    if (!gl3wIsSupported(4, 2)) {
        std::cerr << "OpenGL 4.2 not supported" << std::endl;
		return;
    }
    std::cout << "OpenGL " << glGetString(GL_VERSION) << "\nGLSL "
              << glGetString(GL_SHADING_LANGUAGE_VERSION);


}












