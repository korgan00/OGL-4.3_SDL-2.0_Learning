/*
 * Demo_3.cpp
 *
 *  Created on: 01/07/2013
 *      Author: Korgan
 *
 *  mingw32
 *  glew32
 *  opengl32
 *  SDL2main
 *  SDL2
 *
 */

#include "Demo_OGL_3a.h"

const char* Demo_OGL_3A::WIN_TITLE = "Titulo de la Ventana";
const GLfloat Demo_OGL_3A::cube_positions[] = {
        -0.3f, -0.3f, -0.3f, 1.0f,
        -0.3f, -0.3f,  0.3f, 1.0f,
        -0.3f,  0.3f, -0.3f, 1.0f,
        -0.3f,  0.3f,  0.3f, 1.0f,
         0.3f, -0.3f, -0.3f, 1.0f,
         0.3f, -0.3f,  0.3f, 1.0f,
         0.3f,  0.3f, -0.3f, 1.0f,
         0.3f,  0.3f,  0.3f, 1.0f
};
const GLfloat Demo_OGL_3A::cube_colors[] = {
         1.0f,  1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  0.0f,  1.0f,
         1.0f,  0.0f,  1.0f,  1.0f,
         1.0f,  0.0f,  0.0f,  1.0f,
         0.0f,  1.0f,  1.0f,  1.0f,
         0.0f,  1.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f
};
const GLfloat Demo_OGL_3A::cube_rel_pos[] = {
         -2.0f,   -2.0f,  0.0f,  1.0f,
         -1.0f,   -2.0f,  0.0f,  1.0f,
          0.0f,   -2.0f,  0.0f,  1.0f,
          1.0f,   -2.0f,  0.0f,  1.0f,
          2.0f,   -2.0f,  0.0f,  1.0f,
         -2.0f,   -1.0f,  0.0f,  1.0f,
         -1.0f,   -1.0f,  0.0f,  1.0f,
          0.0f,   -1.0f,  0.0f,  1.0f,
          1.0f,   -1.0f,  0.0f,  1.0f,
          2.0f,   -1.0f,  0.0f,  1.0f,
         -2.0f,    0.0f,  0.0f,  1.0f,
         -1.0f,    0.0f,  0.0f,  1.0f,
          0.0f,    0.0f,  0.0f,  1.0f,
          1.0f,    0.0f,  0.0f,  1.0f,
          2.0f,    0.0f,  0.0f,  1.0f,
         -2.0f,    1.0f,  0.0f,  1.0f,
         -1.0f,    1.0f,  0.0f,  1.0f,
          0.0f,    1.0f,  0.0f,  1.0f,
          1.0f,    1.0f,  0.0f,  1.0f,
          2.0f,    1.0f,  0.0f,  1.0f,
         -2.0f,    2.0f,  0.0f,  1.0f,
         -1.0f,    2.0f,  0.0f,  1.0f,
          0.0f,    2.0f,  0.0f,  1.0f,
          1.0f,    2.0f,  0.0f,  1.0f,
          2.0f,    2.0f,  0.0f,  1.0f,
};
const GLushort Demo_OGL_3A::cube_indices[] = {
        0, 1, 2, 3, 6, 7, 4, 5, // First strip
        0xFFFF, // <<-- This is the restart index
        2, 6, 0, 4, 1, 5, 3, 7 // Second strip*/
};

const vmath::vec3 Demo_OGL_3A::X(1.0f, 0.0f, 0.0f);
const vmath::vec3 Demo_OGL_3A::Y(0.0f, 1.0f, 0.0f);
const vmath::vec3 Demo_OGL_3A::Z(0.0f, 0.0f, 1.0f);

Demo_OGL_3A::Demo_OGL_3A() : running(false), window(NULL), ctxt(NULL), info(),
            aspect(0), render_prog(0),
            render_model_matrix_loc(0), render_projection_matrix_loc(0),
            posX(0.0f), posY(0.0f), posZ(-5.0f){
	ebo[0] = vao[0] = vbo[0] = -1;
	vbo[1] = -1;
}

void Demo_OGL_3A::OnEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_KEYUP:
            switch(event->key.keysym.sym){
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
void Demo_OGL_3A::OnLoop() {}

void Demo_OGL_3A::OnCleanup() {
    glUseProgram(0);
    glDeleteProgram(render_prog);
    glDeleteVertexArrays(1, vao);
    glDeleteBuffers(2, vbo);
    SDL_GL_DeleteContext(ctxt);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Demo_OGL_3A::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    window = SDL_CreateWindow(WIN_TITLE,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WIN_WIDTH, WIN_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(!window)
        return false;

    SetupOpenGL();
    InitData();

    running = true;

    return true;
}
void Demo_OGL_3A::SetupOpenGL(){

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    ctxt = SDL_GL_CreateContext(window);

    SDL_GL_SetSwapInterval(1);

    if (gl3wInit()) {
       std::cout << "Error al Inicializar GL3W" << std::endl;
    }
}
int Demo_OGL_3A::OnExecute() {
    if (!Init())
        return -1;

    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event))
            Event(&event);

        Loop();
        Render();

        if(info.frame()){
            info.fps_ogl_ver_on_window(window, WIN_TITLE);
        }
    }
    Cleanup();
    return 0;
}

void Demo_OGL_3A::InitData(){
    ShaderInfo shaders[] = {
         { GL_VERTEX_SHADER, "../Shaders/Demo_OGL_III/geometry_instancingA.vs.glsl" },
         { GL_FRAGMENT_SHADER, "../Shaders/Demo_OGL_III/simple.fs.glsl" },
         { GL_NONE, NULL }
    };
    render_prog = LoadShaders( shaders );
    glUseProgram( render_prog );

    render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");
    render_projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");

    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(2, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions );
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors), cube_colors);



    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(cube_positions));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    /**************************************
     * GEOMETRY INSTANCING
     **************************************/
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_rel_pos), cube_rel_pos, GL_STATIC_DRAW);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    aspect = float(WIN_HEIGHT) / float(WIN_WIDTH);

    CheckErr();
}

void Demo_OGL_3A::OnRender() {
    float t = float(GetTickCount() & 0x1FFF) / float(0x1FFF);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(render_prog);

    // Calculamos la matriz modelo
    vmath::mat4 model_matrix(vmath::translate(posX, posY, posZ) *
                                vmath::rotate(t * 360.0f, Y) *
                                vmath::rotate(t * 720.0f, Z));

    vmath::mat4 projection_matrix(vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));


    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
    glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);
    glBindVertexArray( vao[0] );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);


#define USE_PRIMITIVE_RESTART 1
#if USE_PRIMITIVE_RESTART

    glEnable(GL_PRIMITIVE_RESTART);

    glPrimitiveRestartIndex(0xFFFF);

    // Dibujamos como triangle strip (aprovechamos los dos vertices
    // anteriores para dibujar el siguiente triangulo)
    // un total de 17 indices y de tipo unsigned short sin offset (NULL)
    // dibujamos tantos cubos como ponga en INSTANCES
    glDrawElementsInstanced(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL, INSTANCES);


#else
    //Dibujamos un strip y otro.
    // Without primitive restart, we need to call two draw commands
    glDrawElementsInstanced(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, NULL, INSTANCES);
    glDrawElementsInstanced(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT,
            (const GLvoid *)(9 * sizeof(GLushort)), INSTANCES);
#endif
    // Buffer swap
    SDL_GL_SwapWindow(window);
}




void Demo_OGL_3A::CheckErr() {
    GLenum err = glGetError();
    if ( err != GL_NO_ERROR )
        std::cerr << "Error: " <<err;
}








