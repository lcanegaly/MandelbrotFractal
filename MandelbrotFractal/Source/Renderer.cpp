#include "Renderer.h"
#include <stdio.h>
#include "glm.hpp"
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

Renderer::Renderer(int width, int height) : width { width },  height { height } {


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
	glGenTextures(2, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//set texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


};



void Renderer::DrawFractal(int windowWidth, int windowHeight, glm::vec2 center = glm::vec2(0.0f,0.0f), double zoom = 1.0)
{

	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(pos, 0.0f));
	//model = glm::scale(model, glm::vec3(size, 1.0f));
	GLint uniformTranslate = glGetUniformLocation(this->program, "translate");
	glUniformMatrix4fv(uniformTranslate, 1, GL_FALSE, glm::value_ptr(model));
	//glUniform1f()
	GLint uniformZoom = glGetUniformLocation(this->program, "zoom");
	glUniform1f(uniformZoom, (float)zoom);

	GLint uniformPan = glGetUniformLocation(this->program, "pan");
	glUniform2f(uniformPan, center.x, center.y);

	glUseProgram(program);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBindTexture(GL_TEXTURE_2D, this->texture);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);
	//glGenerateMipmap(GL_TEXTURE_2D);


	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::Draw(unsigned char* tex, int posX, int posY, int width, int height)
{

	glm::vec2 position = ConvertPixelToNorm(posX, posY);
	glm::vec2 size;
	size.x = (float)width / (float)this->width;
	size.y = (float)height / (float)this->height;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));
	GLint uniformTranslate = glGetUniformLocation(this->program, "translate");
	glUniformMatrix4fv(uniformTranslate, 1, GL_FALSE, glm::value_ptr(model));

	glUseProgram(program);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);
	glGenerateMipmap(GL_TEXTURE_2D);


	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::SetActiveTexture(int texSlot)
{
	switch (texSlot) 
	{
	case 0: glActiveTexture(GL_TEXTURE0);
		break;

	case 1: glActiveTexture(GL_TEXTURE1);
		break;

	default: glActiveTexture(GL_TEXTURE3);
		break;
	}
	

}

void Renderer::PrintStatus()
{

	std::cout << "Texture ID: " << this->texture << std::endl << "VAO: " << this->vao << std::endl << "VBO: " << this->vbo << std::endl;

}

glm::vec2 Renderer::ConvertNormToPixel(glm::vec2 xy)
{

	float outX = ((xy.x + 1.0f) / 2.0f) * this->width;
	float outY = ((xy.y + 1.0f) / 2.0f) * this->height;
	outY = outY * -1; //flip y for drawing

	return glm::vec2(outX, outY);

}

glm::vec2 Renderer::ConvertPixelToNorm(int x, int y)
{
	
	float outX = (((float)x / (float)this->width)*2) - 1;
	float outY = (((float)y / (float)this->height) * 2) - 1;
	outY = outY * -1; //flip y for drawing

	return glm::vec2(outX, outY);
	
}

