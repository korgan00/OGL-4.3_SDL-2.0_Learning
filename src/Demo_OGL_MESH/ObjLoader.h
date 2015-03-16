
#ifndef OBJ_LOADER_H_
#define OBJ_LOADER_H_
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
#include "../Utils/SDL_OGL_GL3W_Dev_GeneralInclude.h"
#include "SDL_image.h"


class ObjLoader {
private:

	typedef GLushort Face[3];
	typedef GLfloat Vertex[3];
	typedef GLfloat TexVertex[2];
	typedef struct {
		Vertex *vertex;
		int vertexCount;
		GLuint sizeOfVertex;

		TexVertex *texCoord;
		int texCoordCount;
		GLuint sizeOfTexCoords;

		Face *faces;
		int facesCount;
		GLuint sizeOfFaces;

		string name;
	} Group;

	SDL_Surface* texture_A;
	GLuint texture_A_id;

	std::string objFile;
	vector<Group> groups;
	GLuint render_prog;
	GLuint render_model_matrix_loc;
	GLuint render_projection_matrix_loc;
	GLuint render_texture_loc;

	GLuint ebo[1];
	GLuint vao[1];
	GLuint vbo[1];
	float aspect;

	void createGroup() {
		Group g = Group();
		g.vertexCount = 0;
		g.texCoordCount = 0;
		g.facesCount = 0;

		groups.push_back(g);
	}

	void initGroup(Group *g) {
		g->vertex = new Vertex[g->vertexCount];
		g->sizeOfVertex = g->vertexCount * sizeof(Vertex);

		g->texCoord = new TexVertex[g->texCoordCount];
		g->sizeOfTexCoords = g->texCoordCount * sizeof(TexVertex);

		g->faces = new Face[g->facesCount];
		g->sizeOfFaces = g->facesCount * sizeof(Face);

		cout << g->vertexCount << "::" << g->texCoordCount << "::" << g->facesCount << endl;
		cout << g->sizeOfVertex << ", " << g->sizeOfTexCoords << ", " << g->sizeOfFaces << endl;
	}


public:

	ObjLoader(std::string objFile, float aspect) : objFile(objFile), groups(0), aspect(aspect) {}

	void load();

	void initOGLData();

	void draw(vmath::mat4 model_matrix, vmath::mat4 projection_matrix);
};




#endif /* OBJ_LOADER_H_ */
