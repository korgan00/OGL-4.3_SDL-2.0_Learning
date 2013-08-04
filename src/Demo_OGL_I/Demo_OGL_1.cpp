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
/*{{  1.00, 0.00, 0.00 }, { -0.90, -0.90 }},  // Triangle 1
        {{  0.00, 1.00, 0.00 }, {  0.85, -0.90 }},
        {{  0.00, 0.00, 1.00 }, { -0.90,  0.85 }},
        {{  0.04, 0.04, 0.04 }, {  0.90, -0.85 }},  // Triangle 2
        {{  0.40, 0.40, 0.40 }, {  0.90,  0.90 }},
        {{  1.00, 1.00, 1.00 }, { -0.85,  0.90 }}*/

#include "Demo_OGL_1.h"
#include <GL/gl3w.h>
#include <GL/gl.h>
#include "LoadShaders.h"

const char* Demo_OGL_1::WIN_TITLE = "Titulo de la Ventana";

Demo_OGL_1::Demo_OGL_1() : running(false), window(NULL), ctxt(NULL){}

void Demo_OGL_1::OnEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_KEYUP:
            switch(event->key.keysym.sym){
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
void Demo_OGL_1::OnLoop() {}

void Demo_OGL_1::OnCleanup() {
    glUseProgram(0);
    glDeleteVertexArrays(1, vao);
    glDeleteBuffers(1, buffer);
    SDL_GL_DeleteContext(ctxt);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int Demo_OGL_1::OnExecute() {
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

void Demo_OGL_1::OnRender() {

    glClear( GL_COLOR_BUFFER_BIT );

    glBindVertexArray( vao[0] );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );

    SDL_GL_SwapWindow(window);
}

bool Demo_OGL_1::OnInit() {
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
void Demo_OGL_1::SetupOpenGL(){

   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
   ctxt = SDL_GL_CreateContext(window);

   //vsync ON
   SDL_GL_SetSwapInterval(1);

   if (gl3wInit()) {
       std::cout << "Error al Inicializar GL3W" << std::endl;
   }

   glClearColor(0.0, 0.0, 0.0, 1.0);

}
void Demo_OGL_1::InitData()
{
    /* Genera un numero de espacios para guardar vertices, pero no
     * son objetos de vertices, simplemente son nombres ("punteros")
     * a donde hay que guardarlo, numVaos es 1 y VAOs es un array de ints
     * De manera informal, busca un sitio para colocar el array y te dice donde
     * */
    glGenVertexArrays( 1, vao );
    /* Inicializamos la zona de memoria del vertexArray del nombre("puntero")
     * que le pasamos. Ademas vuelve activo el vertexArray,
     * Si ya estaba inicializada solo lo vuelve activo.
     * */
    glBindVertexArray( vao[0] );

    struct VertexData {
        GLfloat color[3];
        GLfloat position[4];
    };

    VertexData vertices[NumVertices] = {
        {{  1.00, 0.00, 0.00 }, {  0.00, 0.90 }},
        {{  0.00, 1.00, 0.00 }, {  0.90, -0.90 }},
        {{  0.00, 0.00, 1.00 }, { -0.90, -0.90 }}

    };


    /* Genera un numero de espacios para guardar Buffers pero no son buffers
     * Simplemente tienen espacio para ser guardados.
     * NumBuffers es 1 y buffers es un array de ints.
     * GLuint  Buffers[NumBuffers];
     * */
    glGenBuffers( 1, buffer );
    /* Se crea el objeto buffer y se une al nombre que le hemos dado.
     * ArrayBuffer es 0 a si que es el primero de los nombres (hemos pedido 1 xD)
     * Si ya esta creado no lo crea.
     * En ambos casos lo vuelve asocia a GL_ARRAY_BUFFER
     * */
    glBindBuffer( GL_ARRAY_BUFFER, buffer[0] );
    /* Coge el Buffer object asociado a GL_ARRAY_BUFFER, ademas elije la
     * mejor manera de guardarlo y lo rellena con la
     * informacion de vertices, hay que indicarle el tama�o en bytes.
     * GL_STATIC_DRAW le indica como se va a usar el buffer.
     *
     * Static se va a modificar una vez y a usar muchas.
     * Dynamic se va a modificar muchas veces y se va a usar muchas veces
     * Stream se va a modificar una vez y se va a usar pocas veces
     *
     * Draw se modifica por la aplicacion y lo usa opengl
     * Read se modifica por opengl y lo lee la aplicacion
     * Copy se modifica por opengl y lo lee opengl     *
     * */
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices),
                  vertices, GL_STATIC_DRAW );

    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, "Resources/Demo_OGL_I/gouraud.vert" },
        { GL_FRAGMENT_SHADER, "Resources/Demo_OGL_I/gouraud.frag" },
        { GL_NONE, NULL }
    };

    GLuint program = LoadShaders( shaders );
    glUseProgram( program );

    glVertexAttribPointer( vColor, 3, GL_FLOAT,
                           GL_TRUE, sizeof(VertexData), NULL );
    glVertexAttribPointer( vPosition, 2, GL_FLOAT,
                           GL_FALSE, sizeof(VertexData),
                           (const GLvoid*)sizeof(vertices[0].color) );

    glEnableVertexAttribArray( vColor );
    glEnableVertexAttribArray( vPosition );
}













