/*
* Demo_5.cpp
*
*  Created on: 05/03/2015
*      Author: Korgan
*
*  mingw32
*  glew32
*  opengl32
*  SDL2main
*  SDL2
*
*/

#include "Demo_OGL_5.h"

const char* Demo_OGL_5::WIN_TITLE = "Titulo de la Ventana";
const GLfloat Demo_OGL_5::cube_positions[] = {
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f
};
const GLfloat Demo_OGL_5::cube_colors[] = {
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f
};
const GLfloat Demo_OGL_5::cube_position1[] = { -2.0f, 0.0f, 5.0f };
const GLfloat Demo_OGL_5::cube_position2[] = { 2.0f, 0.0f, 5.0f };

const GLushort Demo_OGL_5::cube_indices[] = {
	0, 1, 2, 3, 6, 7, 4, 5, // First strip
	0xFFFF, // <<-- This is the restart index
	2, 6, 0, 4, 1, 5, 3, 7 // Second strip*/
};

const vmath::vec3 Demo_OGL_5::X(1.0f, 0.0f, 0.0f);
const vmath::vec3 Demo_OGL_5::Y(0.0f, 1.0f, 0.0f);
const vmath::vec3 Demo_OGL_5::Z(0.0f, 0.0f, 1.0f);

Demo_OGL_5::Demo_OGL_5() : running(false), window(NULL), ctxt(NULL), info(),
aspect(0), render_prog1(0), render_prog2(0),
render_model_matrix_loc1(0), render_projection_matrix_loc1(0),
render_model_matrix_loc2(0), render_projection_matrix_loc2(0){
	ebo[0] = vao[0] = vbo[0] = -1;
}

void Demo_OGL_5::OnEvent(SDL_Event* event) {
	switch (event->type) {
	case SDL_KEYUP:
		switch (event->key.keysym.sym){
		case SDLK_v:
			std::cout << std::endl;
			std::cout << info.client_info() << std::endl;
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
void Demo_OGL_5::OnLoop() {}

void Demo_OGL_5::OnCleanup() {
	glUseProgram(0);
	glDeleteProgram(render_prog1);
	glDeleteProgram(render_prog2);
	glDeleteVertexArrays(1, vao);
	glDeleteBuffers(1, vbo);
	SDL_GL_DeleteContext(ctxt);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Demo_OGL_5::OnInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	window = SDL_CreateWindow(WIN_TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!window)
		return false;

	SetupOpenGL();
	InitData();

	running = true;

	return true;
}
void Demo_OGL_5::SetupOpenGL(){

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	ctxt = SDL_GL_CreateContext(window);

	SDL_GL_SetSwapInterval(0);

	if (gl3wInit()) {
		std::cout << "Error al Inicializar GL3W" << std::endl;
	}
}
int Demo_OGL_5::OnExecute() {
	if (!Init())
		return -1;

	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event))
			Event(&event);

		Loop();
		Render();

		if (info.frame()){
			info.fps_ogl_ver_on_window(window, WIN_TITLE);
		}
	}
	Cleanup();
	return 0;
}

void Demo_OGL_5::InitData(){
	// Seleccionamos los shaders que queremos cargar

	ShaderInfo shaders1[] = {
		{ GL_VERTEX_SHADER, "../Shaders/Demo_OGL_V/primitive_restart.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "../Shaders/Demo_OGL_V/primitive_restart.fs.glsl" },
		{ GL_NONE, NULL }
	};
	ShaderInfo shaders2[] = {
		{ GL_VERTEX_SHADER, "../Shaders/Demo_OGL_V/primitive_restart.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "../Shaders/Demo_OGL_V/primitive_restart2.fs.glsl" },
		{ GL_NONE, NULL }
	};

	// Cargamos los shaders
	render_prog1 = LoadShaders(shaders1);
	render_prog2 = LoadShaders(shaders2);
	// Decimos a opengl que los utilice
	glUseProgram(render_prog1);

	// Seleccionamos la posicion dentro del shader de la matriz de modelado y la de proyeccion
	// Mas tarde vamos a usar esas posiciones para cambiar datos del cubo
	render_model_matrix_loc1 = glGetUniformLocation(render_prog1, "model_matrix");
	render_projection_matrix_loc1 = glGetUniformLocation(render_prog1, "projection_matrix");
	
	// Pedimos un buffer para el element buffer object
	glGenBuffers(2, ebo);
	// Le hacemos hueco diciendole el tipo de buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
	// Lo rellenamos con los indices de los cubos
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);
	
	// Pedimos un array de vertices
	glGenVertexArrays(2, vao);
	// Le hacemos hueco
	glBindVertexArray(vao[0]);

	// Pedimos un buffer para el vertex buffer object
	glGenBuffers(2, vbo);
	// Le hacemos hueco
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	// Le decimos que el hueco tiene que ser de tamaño "tamaño de cube positions"+"tamaño de cube colors"
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions)+sizeof(cube_colors)+sizeof(cube_position1), NULL, GL_STATIC_DRAW);
	// Y como lo tenemos en dos arrays diferentes lo guardamos poco a poco
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors), cube_colors);

	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions)+sizeof(cube_colors), sizeof(cube_position1), cube_position1);

	// localizacion del atributo, numero de valores, tipo de valores,
	// normalizarlos, espacio entre valores, puntero al primer valor.
	// Por lo tanto decimos que nos pille los 4 primeros valores y
	// nos los meta en "posicion",
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	// Y apartir de cube positions que pille los colores.
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_positions));
	// Activamos los dos arrays de atributos
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(sizeof(cube_positions)+sizeof(cube_colors)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);




	glUseProgram(render_prog2);
	render_model_matrix_loc2 = glGetUniformLocation(render_prog2, "model_matrix");
	render_projection_matrix_loc2 = glGetUniformLocation(render_prog2, "projection_matrix");


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

	glBindVertexArray(vao[1]);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions)+sizeof(cube_colors)+sizeof(cube_position2), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors), cube_colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions)+sizeof(cube_colors), sizeof(cube_position2), cube_position2);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_positions));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(sizeof(cube_positions)+sizeof(cube_colors)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);



	//Seleccionamos el color de fondo
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Los triangulos que no se ven, ni los pinta (los triangulos que estan de espaldas)
	glEnable(GL_CULL_FACE);
	//Utiliza el z buffer
	glEnable(GL_DEPTH_TEST);
	//Funcion para el z-buffer
	glDepthFunc(GL_LESS);

	//lo que ocupa la parte en la que se dibuja.
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	aspect = float(WIN_HEIGHT) / float(WIN_WIDTH);
}

void Demo_OGL_5::OnRender() {
	// Un numero incremental en funcion del tiempo real
	float t = float(GetTickCount() & 0x1FFF) / float(0x1FFF);

	// Limpiamos el buffer de profundidad (se pone al valor por defecto)
	// y el de color (se pone al valor de glClearColor
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Decimos que Shader usar
	glUseProgram(render_prog1);

	// Calculamos la matriz modelo
	vmath::mat4 model_matrix(vmath::translate(0.0f, 0.0f, -15.0f) *
									vmath::rotate(t * 360.0f, Y) *
									vmath::rotate(t * 720.0f, Z));
	// Calculamos la matriz de proyección mediante un frustum
	vmath::mat4 projection_matrix(vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));

	// Posicion en el shader, cantidad de matrices, es traspuesta? , matriz a setear.
	// Guardamos las dos matrices en el shader para que dibuje.
	// Al ser uniform el valor, se aprovecha entre los shaders
	glUniformMatrix4fv(render_model_matrix_loc1, 1, GL_FALSE, model_matrix);
	glUniformMatrix4fv(render_projection_matrix_loc1, 1, GL_FALSE, projection_matrix);
	// Activamos el vertex array Object
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	// Activamos el buffer de indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
	

#define USE_PRIMITIVE_RESTART 1
#if USE_PRIMITIVE_RESTART
	// When primitive restart is on, we can call one draw command
	// Le decimos que active el reinicio de primitivas,
	glEnable(GL_PRIMITIVE_RESTART);
	// Este es el valor del indice que se toma para el reinicio
	glPrimitiveRestartIndex(0xFFFF);
	// Dibujamos como triangle strip (aprovechamos los dos vertices
	// anteriores para dibujar el siguiente triangulo)
	// un total de 17 indices y de tipo unsigned short sin offset (NULL)
	glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);
#else
	//Dibujamos un strip y otro.
	// Without primitive restart, we need to call two draw commands
	glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, NULL);
	glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT,
		(const GLvoid *)(9 * sizeof(GLushort)));
#endif

	glUseProgram(render_prog2);
	glUniformMatrix4fv(render_model_matrix_loc2, 1, GL_FALSE, model_matrix);
	glUniformMatrix4fv(render_projection_matrix_loc2, 1, GL_FALSE, projection_matrix);
	
	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFF);
	glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL);
	
	// Buffer swap
	SDL_GL_SwapWindow(window);
}












