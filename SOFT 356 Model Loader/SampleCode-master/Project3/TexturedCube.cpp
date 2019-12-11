//////////////////////////////////////////////////////////////////////////////
//
//  Triangles.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "LoadShaders.h"
#include <glm/glm.hpp> //includes GLM
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include <glm/ext/matrix_transform.hpp> // GLM: translate, rotate
#include <glm/ext/matrix_clip_space.hpp> // GLM: perspective and ortho 
#include <glm/gtc/type_ptr.hpp> // GLM: access to the value_ptr
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include<sstream>
#include<string>
#include<fstream>
#include <iostream>
#include<vector>
#include<algorithm>

#include "TexturedCube.h"

using namespace std;

// to use this example you will need to download the header files for GLM put them into a folder which you will reference in
// properties -> VC++ Directories -> libraries

enum VAO_IDs { Triangles, Indices, Colours, Tex, NumVAOs = 1 };
enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
enum Attrib_IDs { vPosition = 0, cPosition = 1, tPosition = 2 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];
GLuint texture1;

const GLuint  NumVertices = 36;

void loadFile(string file_name, vector<GLfloat> & outVertices, vector<GLfloat> & outTextures, vector<GLfloat> & outNormals)
{

	string line;
	ifstream myFile("media/"+ file_name + ".obj"); // Reading in specific file, hardcoded for ease
	vector<GLfloat> vertices;
	vector<GLfloat> textures;
	vector<GLfloat> normals;
	vector<GLuint> vIndices, tIndices, nIndices;

	if (myFile.is_open()) // Opening file
	{
	

		while (getline(myFile, line)) // Reading through each line looking at values of string to seperate
		{
			std::cout << line << std::endl;

			if  (line[0] == 'v' && line[1] == ' ') //Seperating based on char V and char _
			{
				GLfloat fl;

				istringstream data(line.substr(2)); 
				data >> fl;
				vertices.push_back(fl);
				data >> fl;
				vertices.push_back(fl);
				data >> fl;
				vertices.push_back(fl);

				//cout << vertices[0];

			}else
			
			if (line[0] == 'v' && line[1] == 't') //Seperating based on char V and Char T
			{

				GLfloat fl;

				istringstream data(line.substr(2));
				data >> fl;
				textures.push_back(fl);
				data >> fl;
				textures.push_back(fl);
			

				//cout << vertices[0];

			}else

			if (line[0] == 'v' && line[1] == 'n') //Seperating based on char V and char N
			{

				GLfloat fl;

				istringstream data(line.substr(2));
				data >> fl;
				normals.push_back(fl);
				data >> fl;
				normals.push_back(fl);
				data >> fl;
				normals.push_back(fl);

				//cout << vertices[0];

			}else
			
			if(line[0] == 'f' && line[1] == ' ') //Seperating based on char F and char _
			{
				
				replace(line.begin(), line.end(), '/', ' ');  //Replacing the / with _ to make seperating easier

				GLuint tempVertices, tempNormals, tempTextures;
				GLuint vertexIndex[4], textureIndex[4], normalIndex[4], num;
				istringstream data(line.substr(2));
				
				data >> num;
				vertexIndex[0] = num;
			
				data >> num;
				textureIndex[0] = num;
			
				data >> num;
				normalIndex[0] = num;
			

				data >> num;
				vertexIndex[1] = num;
				data >> num;
				textureIndex[1] = num;
				data >> num;
				normalIndex[1] = num;

				data >> num;
				vertexIndex[2] = num;
	
				data >> num;
				textureIndex[2] = num;
				
				data >> num;
				normalIndex[2] = num;
				

				data >> num;
				vertexIndex[3] = num;
				data >> num;
				textureIndex[3] = num;
				data >> num;
				normalIndex[3] = num;

				/*cout << vertexIndex[0] << "/" << textureIndex[0] << "/" << normalIndex[0] << endl;
				cout << vertexIndex[1] << "/" << textureIndex[1] << "/" << normalIndex[1] << endl;
				cout << vertexIndex[2] << "/" << textureIndex[2] << "/" << normalIndex[2] << endl;
				cout << vertexIndex[3] << "/" << textureIndex[3] << "/" << normalIndex[3] << endl;*/

				
					vIndices.push_back(vertexIndex[0]);
					tIndices.push_back(textureIndex[0]);
					nIndices.push_back(normalIndex[0]);

					vIndices.push_back(vertexIndex[1]);
					tIndices.push_back(textureIndex[1]);
					nIndices.push_back(normalIndex[1]);	

					vIndices.push_back(vertexIndex[2]);
					tIndices.push_back(textureIndex[2]);
					nIndices.push_back(normalIndex[2]);

					vIndices.push_back(vertexIndex[0]);
					tIndices.push_back(textureIndex[0]);
					nIndices.push_back(normalIndex[0]);

					vIndices.push_back(vertexIndex[2]);
					tIndices.push_back(textureIndex[2]);
					nIndices.push_back(normalIndex[2]);	

					vIndices.push_back(vertexIndex[3]);
					tIndices.push_back(textureIndex[3]);
					nIndices.push_back(normalIndex[3]);

					

				

				//cout << vertexIndex[0] << "/" << textureIndex[0] << "/" << normalIndex[0] << endl;

			}

		}
		
	}

	for (GLint i = 0; i < vIndices.size(); i++) {
	
		GLint vertexIndex = (vIndices[i] - 1) * 3;
		//GLint textureIndex = (tIndices[i] - 1) * 2;
		GLint normalIndex = (nIndices[i] - 1) * 3;

		/*cout << vIndices[i] << "/" << tIndices[i] << "/" << nIndices[i] << endl;*/

		outVertices.push_back(vertices[vertexIndex]);
		outVertices.push_back(vertices[vertexIndex + 1]);
		outVertices.push_back(vertices[vertexIndex + 2]);
		
		//outTextures.push_back(textures[textureIndex]);
		//outTextures.push_back(textures[textureIndex + 1]);

		outNormals.push_back(normals[normalIndex]);
		outNormals.push_back(normals[normalIndex + 1]);
		outNormals.push_back(normals[normalIndex + 2]);


	}

	for (GLint i = 0; i < tIndices.size(); i++) {

		
		GLint textureIndex = (tIndices[i] - 1) * 2;
		

		/*cout << vIndices[i] << "/" << tIndices[i] << "/" << nIndices[i] << endl;*/

		

		outTextures.push_back(textures[textureIndex]);
		outTextures.push_back(textures[textureIndex + 1]);

	


	}
}

//----------------------------------------------------------------------------
//
// init
//
#define BUFFER_OFFSET(a) ((void*)(a))


void
init(vector<GLfloat>& vertices, vector<GLfloat>& textures, vector<GLfloat>& normals, string texture_name)
{
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	ShaderInfo  shaders[] =
	{
		{ GL_VERTEX_SHADER, "media/triangles.vert" },
		{ GL_FRAGMENT_SHADER, "media/triangles.frag" },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);


	GLuint indices[][3] = {  // note that we start from 0!
		{0, 3, 1},  // first Triangle front
		{3, 2, 1},   // second Triangle
		
		{4, 7, 0 },
		{7, 3, 0 },
		
		{1, 2, 5 },
		{2, 6, 5 },
		
		{5, 4, 0 },
		{0, 1, 5 },
		
		{2, 3, 7 },
		{7, 6, 2 },
		
		{4, 5, 7 },  // first Triangle back
		{7, 5, 6 }   // second Triangle
	};

	GLfloat  colours[][4] = {
		{ 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f },  
		{ 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, 
		{ 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, 
	};
	GLfloat  texture_coords[] = {
		 1.0f, 1.0f,
		 1.0f, 0.0f,
		 0.0f, 0.0f,
		 0.0f, 1.0f,

		 0.0f, 1.0f,
	     0.0f, 0.0f,
		 1.0f, 0.0f,
		 1.0f, 1.0f,

		
	
	};



	glGenBuffers(NumBuffers, Buffers);
	
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[Indices]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	

	glVertexAttribPointer(vPosition, 3, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));
	
	//Colour Binding
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Colours]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(colours), colours, 0);


	glVertexAttribPointer(cPosition, 4, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));

	//Texture Binding
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Tex]);
	glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(GLfloat), textures.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(tPosition, 2, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));

	loadTexture(texture1, texture_name);
	glUniform1i(glGetUniformLocation(program, "texture1"), 0);

	// creating the model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));

	// creating the view matrix
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

	// creating the projection matrix
	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3, 0.1f, 20.0f);

	// Adding all matrices up to create combined matrix
	glm::mat4 mvp = projection * view * model;


	//adding the Uniform to the shader
	int mvpLoc = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(cPosition); 
	glEnableVertexAttribArray(tPosition);
}

void loadTexture(GLuint &texture, std::string texturepath)
{
	// load and create a texture 
// -------------------------

// texture 1
// ---------
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	GLint width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load(texturepath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}


//----------------------------------------------------------------------------
//
// display
//


void
display(void)
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, black);
	glClear(GL_COLOR_BUFFER_BIT);
	// bind textures on corresponding texture units
	//glFrontFace(GL_CW);
	// glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glBindVertexArray(VAOs[Triangles]);
	glBindTexture(GL_TEXTURE_2D, texture1);
	/*glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_INT, 0);
*/glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	
}

void
loadMTLFile(string file_name, vector<GLfloat> & colour, vector<GLfloat> & diffuse, vector<GLfloat> & specular, GLfloat & ns, string& texture_name)
{

	string line;
	ifstream myFile("media/" + file_name + ".mtl"); // Reading in specific file, hardcoded for ease
	GLfloat transparency = -1;


	if (myFile.is_open()) // Opening file
	{
		GLfloat fl;
		

		while (getline(myFile, line)) // Reading through each line looking at values of string to seperate
		{
			std::cout << line << std::endl;

			if (line[0] == 'K' && line[1] == 'a') 
			{
				
				istringstream data(line.substr(2));
				data >> fl;
				colour.push_back(fl);

				data >> fl;
				colour.push_back(fl);

				data >> fl;
				colour.push_back(fl);

				data >> fl;
				colour.push_back(fl);


			}
			else
				
			if (line[0] == 'd' && line[1] == ' ')
			{

				istringstream data(line.substr(2));
				data >> fl;
				transparency = fl;

				if (transparency == -1)
				{
					transparency = 1;
				}
				
				colour.push_back(transparency);

			}
			else

			if (line[0] == 'K' && line[1] == 'd') 
			{


				istringstream data(line.substr(2));
				data >> fl;
				diffuse.push_back(fl);

				data >> fl;
				diffuse.push_back(fl);
				
				data >> fl;
				diffuse.push_back(fl);
			}
			else

			if (line[0] == 'K' && line[1] == 's') 
			{

				istringstream data(line.substr(2));
				data >> fl;
				specular.push_back(fl);

				data >> fl;
				specular.push_back(fl);

				data >> fl;
				specular.push_back(fl);


			}
			else

			if (line[0] == 'N' && line[1] == 's') 
			{

							
				istringstream data(line.substr(2));
				data >> fl;
				ns = fl;

			}else

			if (line.substr(0,6) == "map_Kd")
			{
				
				istringstream data(line.substr(7));
				texture_name = data.str();


			}

		}

		texture_name = "media/textures/" + texture_name;
		

	}

}
//----------------------------------------------------------------------------
//
// main
//



int
main(int argc, char** argv)
{

	vector<GLfloat>vertices;
	vector<GLfloat>textures;
	vector<GLfloat>normals;
	vector<GLfloat> colour; //Ambient
	GLfloat transparency = -1;
	vector<GLfloat> diffuse;
	vector<GLfloat> specular;
	GLfloat ns; //Specular Exponent
	string texture_name;

	string file_name;

	cin >> file_name;


	loadFile(file_name, vertices, textures, normals);
	loadMTLFile(file_name, colour, diffuse, specular, ns, texture_name);
	
	glfwInit();
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "Textured Cube", NULL, NULL);

	glfwMakeContextCurrent(window);
	glewInit();

	init(vertices, textures, normals, texture_name);

	while (!glfwWindowShouldClose(window))
	{
		// uncomment to draw only wireframe 
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}
