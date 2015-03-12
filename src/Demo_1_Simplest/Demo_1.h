/*
 * Demo_1.h
 *
 *  Created on: 01/07/2013
 *      Author: Korgan
 *
 *  Based on:
 *  http://www.sdltutorials.com/sdl-tutorial-basics
 *  http://www.libsdl.org/docs/html/guidebasicsinit.html
 */

#ifndef DEMO_1_H_
#define DEMO_1_H_

#include "../Utils/SDL_OGL_GL3W_Dev_GeneralInclude.h"

class Demo_1 {
private:
    SDL_Window* mainwindow;
    bool running;
    static const uint32_t WIN_HEIGHT = 512; //px
    static const uint32_t WIN_WIDTH  = 512; //px

public:
    Demo_1();
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

};


#endif /* DEMO_1_H_ */
