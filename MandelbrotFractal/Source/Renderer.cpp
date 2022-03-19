#include "Renderer.h"
#include <stdio.h>
#include "glm.hpp"
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

Renderer::Renderer() {

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	this->program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glUseProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	//texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//set texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

};


/*
void Renderer::Draw(unsigned char* tex, int width, int height) 
{
	
	glUseProgram(program);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);
	glGenerateMipmap(GL_TEXTURE_2D);

	//glUseProgram(program);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
*/

void Renderer::DrawFractal(unsigned char* tex, int windowWidth, int windowHeight)
{

	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(pos, 0.0f));
	//model = glm::scale(model, glm::vec3(size, 1.0f));
	GLint uniformTranslate = glGetUniformLocation(this->program, "translate");
	glUniformMatrix4fv(uniformTranslate, 1, GL_FALSE, glm::value_ptr(model));

	glUseProgram(program);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);
	glGenerateMipmap(GL_TEXTURE_2D);


	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::Draw(unsigned char* tex, glm::vec2 pos, glm::vec2 size)
{

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(pos, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));
	GLint uniformTranslate = glGetUniformLocation(this->program, "translate");
	glUniformMatrix4fv(uniformTranslate, 1, GL_FALSE, glm::value_ptr(model));

	glUseProgram(program);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_DYNAMIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);
	glGenerateMipmap(GL_TEXTURE_2D);


	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::PrintStatus()
{

	std::cout << "Texture ID: " << this->texture << std::endl << "VAO: " << this->vao << std::endl << "VBO: " << this->vbo << std::endl;

}


