
#include "ObjLoader.h"

void ObjLoader::load() {
	

	


	string line;
	GLfloat x, y, z;
	Group *current = &(Group());
	current->vertexCount = 0;
	current->texCoordCount = 0;
	current->facesCount = 0;
	int i = 0;

	// OPEN FILE
	ifstream input("../Resources/Cubo.obj");
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
					case 't': groups.back().texCoordCount++; break;
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
						groups[currentGroup].texCoord[currentTextCoord][0] = x;
						groups[currentGroup].texCoord[currentTextCoord][1] = y;
						//groups[currentGroup].textCoord[currentTextCoord][2] = z;
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
		{ GL_VERTEX_SHADER, "../Shaders/Demo_OGL_MESH/texture.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "../Shaders/Demo_OGL_MESH/texture.fs.glsl" },
		{ GL_NONE, NULL }
	};

	render_prog = LoadShaders(shaders1);
	glUseProgram(render_prog);
	render_texture_loc = glGetUniformLocation(render_prog, "texture_diffuse");
	glUniform1i(render_texture_loc, 0); //Texture unit 0 is for base images.
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
	glGenBuffers(2, vbo);
	// Le hacemos hueco
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	// Le decimos que el hueco tiene que ser de tamaño "tamaño de cube positions"+"tamaño de cube colors"
	glBufferData(GL_ARRAY_BUFFER, group.sizeOfVertex + group.sizeOfTexCoords, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, group.sizeOfVertex, group.vertex);
	glBufferSubData(GL_ARRAY_BUFFER, group.sizeOfVertex, group.sizeOfTexCoords, group.texCoord);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 0, (const GLvoid*)(group.sizeOfVertex));


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	texture_A_id = 0;

	// You should probably use CSurface::OnLoad ... ;)
	//-- and make sure the Surface pointer is good!
	texture_A = IMG_Load("../Resources/ObjTex/texture.jpg");

	glActiveTexture(GL_TEXTURE0 + 0);
	glGenTextures(1, &texture_A_id);
	glBindTexture(GL_TEXTURE_2D, texture_A_id);
	glBindSampler(0, GL_LINEAR);

	int mode = GL_RGB;
	if (texture_A->format->BytesPerPixel == 4) mode = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, mode, texture_A->w, texture_A->h, 0, mode, GL_UNSIGNED_BYTE, texture_A->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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


	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture_A_id);

	//Dibujamos un strip y otro.
	// Without primitive restart, we need to call two draw commands
	glDrawElements(GL_TRIANGLES, groups.front().facesCount * 3, GL_UNSIGNED_SHORT, NULL);
}











