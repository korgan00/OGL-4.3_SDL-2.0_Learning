/*
 * Demo_3.h
 *
 *  Created on: 01/07/2013
 *      Author: Korgan
 */

#ifndef DEMO_3_H_
#define DEMO_3_H_
#include "SDL2/SDL.h"

class Demo_3 {
private:
    bool running;
    SDL_Window* window;
    SDL_GLContext ctxt;

    int aux;

    static const uint32_t   WIN_HEIGHT = 512; //px
    static const uint32_t   WIN_WIDTH  = 512; //px
    static const char*      WIN_TITLE; //px
public:

    Demo_3();
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



    void setupOpenGl();

};


#endif /* DEMO_3_H_ */
