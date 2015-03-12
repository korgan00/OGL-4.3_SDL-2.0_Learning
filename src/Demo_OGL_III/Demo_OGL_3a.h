/*
 * Demo_3.h
 *
 *  Created on: 01/07/2013
 *      Author: Korgan
 */

#ifndef DEMO_OGL_IIIA_H_
#define DEMO_OGL_IIIA_H_
#include <iostream>
#include <string>
#include <sstream>

#include "../Utils/SDL_OGL_GL3W_Dev_GeneralInclude.h"


class Demo_OGL_3A {
private:
    bool running;
    SDL_Window* window;
    SDL_GLContext ctxt;

    static const uint32_t   WIN_HEIGHT = DEFAULT_WIN_HEIGHT;
    static const uint32_t   WIN_WIDTH  = DEFAULT_WIN_WIDTH;
    static const char*      WIN_TITLE; //px
    static const int32_t    INST_LENGTH = 5;
    static const int32_t    INSTANCES = INST_LENGTH*INST_LENGTH;
    Info_Manager info;
    /***************************************************/
    /***************************************************/
    /***************************************************/


    float aspect;
    static const GLfloat cube_positions[];
    static const GLfloat cube_colors[];
    static const GLfloat cube_rel_pos[INSTANCES*4];
    static const GLushort cube_indices[];

    static const vmath::vec3 X;
    static const vmath::vec3 Y;
    static const vmath::vec3 Z;
    GLuint ebo[1];
    GLuint vao[1];
    GLuint vbo[2];

    GLuint render_prog;
    GLuint render_model_matrix_loc;
    GLuint render_projection_matrix_loc;

    GLfloat posX;
    GLfloat posY;
    GLfloat posZ;

public:

    Demo_OGL_3A();

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
    /***************************************************/
    /***************************************************/

    void SetupOpenGL();
    void InitData();

    void CheckErr();
};


#endif /* DEMO_OGL_I_H_ */
