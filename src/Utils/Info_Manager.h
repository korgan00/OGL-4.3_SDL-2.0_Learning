/*
 * FPS_Ctrlr.h
 *
 *  Created on: 17/07/2013
 *      Author: Korgan
 */

#ifndef FPS_CTRLR_H_
#define FPS_CTRLR_H_
#include <iostream>
#include <string>
#include <sstream>
#include <GL/gl3w.h>
#include <GL/gl3.h>
#include "SDL2/SDL.h"
#include "LoadShaders.h"


class Info_Manager {
private:
    Uint32 _last_time_FPS;
    Uint32 _frames;
    Uint32 _fps;
public:
    Info_Manager() : _last_time_FPS(SDL_GetTicks()), _frames(0), _fps(0){}

    bool frame(){
        _frames++;
        //Por si llega al limite de los int
        if (_last_time_FPS - 1000 > SDL_GetTicks()){
            _last_time_FPS = SDL_GetTicks();
            _frames = 0;
        }
        if ((_last_time_FPS + 1000) <= SDL_GetTicks()){
            _last_time_FPS += 1000;
            _fps = _frames;
            _frames = 0;
            return true;
        }
        return false;
    }
    Uint32 fps(){
        return _fps;
    }
    void fps_ogl_ver_on_window(SDL_Window* window, const char* win_title){
        std::stringstream sstring;
        sstring << win_title << " [FPS: " << _fps
                << ", OGL-version: " << glGetString(GL_VERSION)
                << "]";
        std::string s = sstring.str();
        SDL_SetWindowTitle(window, s.c_str());
    }
    const char* client_info(){
        std::stringstream sstring;
        sstring << "--------------------------------------------------------" << std::endl
                << " + OGL-version: " << glGetString(GL_VERSION) << std::endl
                << " + GLSL-version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl
                << " + Vendor: " << glGetString(GL_VENDOR) << std::endl
                << " + Renderer: " << glGetString(GL_RENDERER) << std::endl
                << "--------------------------------------------------------" << std::endl;
        std::string s = sstring.str();
        return s.c_str();
    }

};

#endif /* FPS_CTRLR_H_ */
