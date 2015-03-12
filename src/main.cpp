/*
 * main.cpp
 *
 *  Created on: 28/06/2013
 *      Author: Korgan
 * Description: Contains main function to test demos.
 */

#include <iostream>
#include <iomanip>

#include "HelloWorlds/HW.h"
#include "Demo_1_Simplest/Demo_1.h"
#include "Demo_2_Events_I/Demo_2.h"
#include "Demo_3_OGL_Init/Demo_3.h"
#include "Demo_OGL_I/Demo_OGL_1.h"
#include "Demo_OGL_II/Demo_OGL_2.h"
#include "Demo_OGL_III/Demo_OGL_3a.h"
#include "Demo_OGL_III/Demo_OGL_3b.h"
#include "Demo_OGL_IV/Demo_OGL_4.h"
#include "Demo_OGL_V/Demo_OGL_5.h"
#include "Demo_OGL_MESH/Demo_OGL_Mesh.h"

int demo_selector_menu();
int demo_selector();
int mainDemo_1();
int mainDemo_2();
int mainDemo_3();
int mainDemo_OGL_I();
int mainDemo_OGL_II();
int mainDemo_OGL_IIIA();
int mainDemo_OGL_IIIB();
int mainDemo_OGL_IV();
int mainDemo_OGL_V();
int mainDemo_OGL_Mesh();

/*
 * Este main esta preparado para probar el ejemplo deseado,
 * Descomentando la linea elegida y comentando el resto, pruebas ese ejemplo.
 * Si quieres probarlas una a una puedes descomentar demo_selector que te
 * mostrara un menu para elegir la demo que quieres probar en esa ejecucion.
 */
int main(int argc, char* argv[]) {
	return
		demo_selector()+
		/********************************/
		/*********** BEGINNING **********/
		/********************************/
		//mainDemo_1()+//Ejecución de un juego, fases y organizacion
		//mainDemo_2()+//Gestion de Eventos (teclado, raton...)
		//mainDemo_3()+//Inicializacion de OpenGL


		/********************************/
		/********** OpenGL 4.3 **********/
		/********************************/

		//mainDemo_OGL_I()+//Triangulo
		//mainDemo_OGL_II()+//Cubo
		//mainDemo_OGL_IIIA()+//Hardware/Geometry Instancing
		//mainDemo_OGL_IIIB()+//Exploracion de la escena y mas cubos
		//mainDemo_OGL_IV()+//Texturas No disponible todavia
		//mainDemo_OGL_V()+//Texturas No disponible todavia
		//mainDemo_OGL_Mesh()+//
    0;
}

int demo_selector_menu(){
	int opt = -1;
	int WIDTH = 24;

	std::cout << "\t\t\t\xC9" << 
			"\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD" << 
			"\xCD\xCD\xCD\xCD\xCD" <<
			"\xBB" << std::endl;
	std::cout<< 
			"\t\t\t\xBA SDL-OGL DEMOS \xBA " << std::endl;
	std::cout << "\t\t\t\xC8" << 
			"\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD" << 
			"\xCD\xCD\xCD\xCD\xCD" <<
			"\xBC" << std::endl;
	std::cout << std::endl;
	std::cout << std::setfill('.') << std::setiosflags(std::ios::left) << std::setw(WIDTH) << 
			"\t1.  Demo_1" << "Simplest" << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(WIDTH) << 
			"\t2.  Demo_2" << "Events_I" << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(WIDTH) << 
			"\t3.  Demo_3" << "OGL_Init" << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(WIDTH) << 
			"\t4.  Demo_OGL_1" << "Triangle, Gouraud Shading." << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(WIDTH) << 
			"\t5.  Demo_OGL_2" << "Cube." << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(WIDTH) << 
			"\t6.  Demo_OGL_3A" << "MultiCube, Geometry Instancing." << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(WIDTH) << 
			"\t7.  Demo_OGL_3B" << "MultiCube++, Scene exploring." << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(WIDTH) <<
			"\t8.  Demo_OGL_4" << "Alpha Blending." << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(WIDTH) <<
			"\t9.  Demo_OGL_5" << "Two shaders, same scene." << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(WIDTH) <<
			"\t10. Demo_OGL_Mesh" << "Loading a Mesh." << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(8) << 
			"\t0. Salir." << std::endl;
		
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "\t\xC9" << 
			"\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD" << 
			"\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD" << std::endl;
	std::cout << "\t\xBA Choose demo: ";
	std::cin >> opt;
	std::cout << "\t\xC8" << 
			"\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD" << std::endl;
	return opt;
}

int demo_selector(){
	int opt = -1;
	int retVal = 0;
	while (opt == -1){
		opt = demo_selector_menu();

		switch (opt){
		case 0:  retVal = 0;					break;
		case 1:  retVal = mainDemo_1();			break;
		case 2:  retVal = mainDemo_2();			break;
		case 3:  retVal = mainDemo_3();			break;
		case 4:  retVal = mainDemo_OGL_I();		break;
		case 5:  retVal = mainDemo_OGL_II();	break;
		case 6:  retVal = mainDemo_OGL_IIIA();	break;
		case 7:  retVal = mainDemo_OGL_IIIB();	break;
		case 8:  retVal = mainDemo_OGL_IV();	break;
		case 9:  retVal = mainDemo_OGL_V();		break;
		case 10: retVal = mainDemo_OGL_Mesh();	break;
		default:
			opt = -1;
			std::cout << "WTF!!!!" << std::endl;
			break;
		}
	}
	system("PAUSE");
	return retVal;
}

int mainDemo_1(){
	std::cout << "\t Demo Output: " << std::endl;
    Demo_1 d;
    return d.Execute();
}
int mainDemo_2(){
	std::cout << "\tTip: Mueve el raton y haz click para mostrar eventos de raton" << std::endl;
	std::cout << "\t     Presiona ESC o cierra la ventana para finalizar." << std::endl;
	std::cout << "\t Demo Output: " << std::endl;
    Demo_2 d;
    return d.Execute();
}
int mainDemo_3(){
	std::cout << "\tTip: Pulsa \"+\" o \"-\" para cambiar el color de relleno" << std::endl;	
	std::cout << "\t Demo Output: " << std::endl;
    Demo_3 d;
    return d.Execute();
}
int mainDemo_OGL_I(){
	std::cout << "\t Demo Output: " << std::endl;
    Demo_OGL_1 d;
    return d.Execute();
}
int mainDemo_OGL_II(){
	std::cout << "\t Demo Output: " << std::endl;
    Demo_OGL_2 d;
    return d.Execute();
}
int mainDemo_OGL_IIIA(){
	std::cout << "\t Demo Output: " << std::endl;
    Demo_OGL_3A d;
    return d.Execute();
}
int mainDemo_OGL_IIIB(){
	std::cout << "\t Demo Output: " << std::endl;
    Demo_OGL_3B* d = new Demo_OGL_3B();
    return d->Execute();
}
int mainDemo_OGL_IV(){
	std::cout << "\t Demo Output: " << std::endl;
	Demo_OGL_4* d = new Demo_OGL_4();
	return d->Execute();
}
int mainDemo_OGL_V(){
	std::cout << "\t Demo Output: " << std::endl;
	Demo_OGL_5* d = new Demo_OGL_5();
	return d->Execute();
}
int mainDemo_OGL_Mesh() {
	std::cout << "\t Demo Output: " << std::endl;
	Demo_OGL_Mesh* d = new Demo_OGL_Mesh();
	return d->Execute();
}

