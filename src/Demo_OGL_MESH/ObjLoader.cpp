
#include "ObjLoader.h"

void ObjLoader::load() {
	string line;
	GLfloat x, y, z;
	Group *current = &(Group());
	current->vertexCount = 0;
	current->textCoordCount = 0;
	current->facesCount = 0;
	int i = 0;

	// OPEN FILE
	ifstream input("../Resources/Arid.obj");
	if (!input.is_open()) {
		cout << "Unable to open file\n";
		return;
	}

	/******* INITIALICE ARRAYS *******/
	// create first group
	createGroup();

	// count vertex and create all groups and group-arrays
	while (getline(input, line)) {
		switch (line[0]) {
			case 'v':
				switch (line[1]) {
					case ' ': groups.back().vertexCount++; break;
					case 't': groups.back().textCoordCount++; break;
				}
			break;
			case 'f': current->facesCount++; break;
			case 'g':
				if (current->vertexCount != 0) initGroup(current);

				createGroup();
				current = &(groups[groups.size() - 2]);
			break;
			default:;
		}
	}
	// finish initializations
	initGroup(current);
	groups.pop_back();
	input.clear();
	input.seekg(0);

	cout << "Populating vertex" << endl;

	/******* POPULATING ARRAYS *******/
	int currentVertex = 0;
	int accumulatedVertex = 1;
	int lastVertexCount = 0;

	int currentTextCoord = 0;
	int currentFace = 0;
	int currentGroup = 0;
	int xFace, yFace, zFace;
	char auxCString[100];
	while (getline(input, line)) {
		switch (line[0]) {
			case 'v': // Vertices & textures
				sscanf(line.c_str(), "%s %f %f %f", &auxCString, &x, &y, &z);
				switch (line[1]) {
					case ' ':
						groups[currentGroup].vertex[currentVertex][0] = x;
						groups[currentGroup].vertex[currentVertex][1] = y;
						groups[currentGroup].vertex[currentVertex][2] = z;
						currentVertex++;
					break;
					case 't':
						groups[currentGroup].textCoord[currentTextCoord][0] = x;
						groups[currentGroup].textCoord[currentTextCoord][1] = y;
						groups[currentGroup].textCoord[currentTextCoord][2] = z;
						currentTextCoord++;
					break;
					default:;
				}
				break;
			case 'f': // Faces (Triangles)
				sscanf(line.c_str(), "f %f/%d %f/%d %f/%d", &x, &xFace, &y, &yFace, &z, &zFace);
				groups[currentGroup - 1].faces[currentFace][0] = xFace - accumulatedVertex;
				groups[currentGroup - 1].faces[currentFace][1] = yFace - accumulatedVertex;
				groups[currentGroup - 1].faces[currentFace][2] = zFace - accumulatedVertex;
				currentFace++;
			break;
			case 'g': // Group
				sscanf(line.c_str(), "g %s", &auxCString);
				current->name = string(auxCString);
				cout << current->name << endl; //Mesh_Arid_{A,B, ... , J}_XX de aqui se puede sacar la textura

				// Next group, reset other counters
				currentGroup++;
				accumulatedVertex += lastVertexCount;
				lastVertexCount = currentVertex;
				currentVertex = 0;
				currentTextCoord = 0;
				currentFace = 0;

				break;
			default:;
		}
	}
	// Close file
	input.close();
}

void ObjLoader::initOGLData() {

	// Seleccionamos los shaders que queremos cargar
	ShaderInfo shaders1[] = {
		{ GL_VERTEX_SHADER, "../Shaders/Demo_OGL_MESH/primitive_restart.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "../Shaders/Demo_OGL_MESH/primitive_restart.fs.glsl" },
		{ GL_NONE, NULL }
	};

	render_prog = LoadShaders(shaders1);
	glUseProgram(render_prog);
	render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");
	render_projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");

	Group group = groups.front();
	// Pedimos un buffer para el element buffer object
	glGenBuffers(1, ebo);
	// Le hacemos hueco diciendole el tipo de buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
	// Lo rellenamos con los indices de los cubos
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, group.sizeOfFaces, group.faces, GL_STATIC_DRAW);

	// Pedimos un array de vertices
	glGenVertexArrays(1, vao);
	// Le hacemos hueco
	glBindVertexArray(vao[0]);

	// Pedimos un buffer para el vertex buffer object
	glGenBuffers(1, vbo);
	// Le hacemos hueco
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	// Le decimos que el hueco tiene que ser de tamaño "tamaño de cube positions"+"tamaño de cube colors"
	glBufferData(GL_ARRAY_BUFFER, group.sizeOfVertex, group.vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);


}

void ObjLoader::draw(vmath::mat4 model_matrix, vmath::mat4 projection_matrix) {

	// Decimos que Shader usar
	glUseProgram(render_prog);

	// Posicion en el shader, cantidad de matrices, es traspuesta? , matriz a setear.
	// Guardamos las dos matrices en el shader para que dibuje.
	// Al ser uniform el valor, se aprovecha entre los shaders
	glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix);
	glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);
	// Activamos el vertex array Object
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	// Activamos el buffer de indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);


	//Dibujamos un strip y otro.
	// Without primitive restart, we need to call two draw commands
	glDrawElements(GL_TRIANGLES, groups.front().facesCount * 3, GL_UNSIGNED_SHORT, NULL);
}











