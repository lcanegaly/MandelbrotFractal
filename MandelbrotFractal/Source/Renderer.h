#pragma once
#include "GL/glew.h"
#include "glm.hpp"
#include <iostream>

class Renderer
{

public:

	Renderer(int width, int height);
	void DrawFractal(unsigned char* tex, int windowWidth, int windowHeight);
	void Draw(unsigned char* tex, int posX, int posY, int width, int height);
	void SetActiveTexture(int texSlot);
	void PrintStatus();
	
	glm::vec2 ConvertNormToPixel(glm::vec2 xy);
	glm::vec2 ConvertPixelToNorm(int x, int y);
	
private:

	int width, height;
	GLuint vbo;
	unsigned int vao;
	GLuint program;
	GLuint texture;

	float vertices[30] = {
	// first triangle
	 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,  // top right
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f, // top left 
	// second triangle
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f // top left
	};

	
	float vertices2[30] = {
	// first triangle
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // top right
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // top left 
	// second triangle
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f // top left
	};
	


	const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec2 aTexCoord;\n"
	"out vec2 TexCoord;\n"
	"uniform mat4 translate;\n"
    "void main()\n"
    "{\n"
    //"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"gl_Position = translate * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"TexCoord = aTexCoord;\n"
		"}\0";


	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D Texture;\n"
		"void main()\n"
		"{\n"
		"	FragColor = texture(Texture, TexCoord);\n"
		"}\0";

	/*
	float texCoords[8] = {
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
	};
	*/

};

