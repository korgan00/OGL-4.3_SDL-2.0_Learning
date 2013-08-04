/*
 * main.cpp
 *
 *  Created on: 28/06/2013
 *      Author: Korgan
 */

#include <iostream>

#include "HelloWorlds/HW.h"
#include "Demo_1_Simplest/Demo_1.h"
#include "Demo_2_Events_I/Demo_2.h"
#include "Demo_3_OGL/Demo_3.h"
#include "Demo_OGL_I/Demo_OGL_1.h"
#include "Demo_OGL_II/Demo_OGL_2.h"
#include "Demo_OGL_III/Demo_OGL_3.h"
#include "SDL2/SDL.h"


int mainDemo_1();
int mainDemo_2();
int mainDemo_3();
int mainDemo_OGL_I();
int mainDemo_OGL_II();
int mainDemo_OGL_III();
/*
 * Este main esta preparado para probar el ejemplo deseado,
 * Descomentando la linea elegida y comentando el resto pruebas ese ejemplo.
 */
int main(int argc, char* argv[]) {

    return
    /********************************/
    /********* HELLO WORLDS *********/
    /********************************/
    //mainHW1()+//Comprobacion de SDL
    //mainHW2()+//Comprobacion de OpenGL
    //mainHW3()+//Comprobacion de carga de Imagenes SDL

    /********************************/
    /*********** BEGINNING **********/
    /********************************/
    //mainDemo_1()+//Ejecución de un juego, fases y organizacion
    //mainDemo_2()+//Gestion de Eventos (teclado, raton...)
    //mainDemo_3()+//Inicializacion de OpenGL


    /********************************/
    /********** OpenGL 4.3 **********/
    /********************************/

    //mainDemo_OGL_I()+
    //mainDemo_OGL_II()+
    mainDemo_OGL_III()+
    0;
}

int mainDemo_1(){
    Demo_1 d;
    return d.Execute();
}
int mainDemo_2(){
    Demo_2 d;
    return d.Execute();
}
int mainDemo_3(){
    Demo_3 d;
    return d.Execute();
}
int mainDemo_OGL_I(){
    Demo_OGL_1 d;
    return d.Execute();
}
int mainDemo_OGL_II(){
    Demo_OGL_2 d;
    return d.Execute();
}
int mainDemo_OGL_III(){
    Demo_OGL_3 d;
    return d.Execute();
}
