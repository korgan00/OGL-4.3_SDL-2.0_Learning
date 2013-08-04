/*
 * Demo_3.h
 *
 *  Created on: 01/07/2013
 *      Author: Korgan
 */

#ifndef DEMO_OGL_I_H_
#define DEMO_OGL_I_H_
#include <iostream>
#include <GL/gl3w.h>
#include <GL/gl.h>
#include "SDL2/SDL.h"
#include "LoadShaders.h"

class Demo_OGL_1 {
private:
    bool running;
    SDL_Window* window;
    SDL_GLContext ctxt;

    static const uint32_t   WIN_HEIGHT = 512; //px
    static const uint32_t   WIN_WIDTH  = 512; //px
    static const char*      WIN_TITLE; //px

    /***************************************************/

    enum Attrib_Locs { vPosition = 0, vColor = 1 };

    GLuint  vao[1];
    GLuint  buffer[1];

    static const GLuint  NumVertices = 3;
public:

    Demo_OGL_1();
    /*
     * GAME LOOP FUNCTIONS
     */

    int Execute(){ return OnExecute(); }
    bool Init(){ return OnInit(); }
    void Loop(){ return OnLoop(); }
    void Render(){ return OnRender(); }
    void Cleanup(){ return OnCleanup(); }
    void Event(SDL_Event* Event){ OnEvent(Event); }


    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event* Event);
    void OnLoop();
    void OnRender();
    void OnCleanup();

    /***************************************************/

    void SetupOpenGL();
    void InitData();
};


#endif /* DEMO_OGL_I_H_ */
