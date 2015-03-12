/*
* Demo_5.h
*
*  Created on: 05/03/2015
*      Author: Korgan
*/

#ifndef DEMO_OGL_V_H_
#define DEMO_OGL_V_H_
#include <iostream>
#include <string>
#include <sstream>

#include "../Utils/SDL_OGL_GL3W_Dev_GeneralInclude.h"



class Demo_OGL_5 {
private:
	bool running;
	SDL_Window* window;
	SDL_GLContext ctxt;

	static const uint32_t   WIN_HEIGHT = DEFAULT_WIN_HEIGHT;
	static const uint32_t   WIN_WIDTH = DEFAULT_WIN_WIDTH;
	static const char*      WIN_TITLE; //px
	Info_Manager info;
	/***************************************************/
	/***************************************************/
	/***************************************************/


	float aspect;
	static const GLfloat cube_positions[];
	static const GLfloat cube_colors[];
	static const GLushort cube_indices[];
	static const GLfloat cube_position1[];
	static const GLfloat cube_position2[];
	static const vmath::vec3 X;
	static const vmath::vec3 Y;
	static const vmath::vec3 Z;
	GLuint ebo[2];
	GLuint vao[2];
	GLuint vbo[2];

	GLuint render_prog1;
	GLuint render_prog2;
	GLuint render_model_matrix_loc1;
	GLuint render_projection_matrix_loc1;
	GLuint render_model_matrix_loc2;
	GLuint render_projection_matrix_loc2;

public:

	Demo_OGL_5();

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
};


#endif /* DEMO_OGL_V_H_ */
