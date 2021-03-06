#include "Renderer.h"
#include <stdio.h>
#include <iostream>
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shaders.h"

Renderer::Renderer() 
	: m_Width{ 0 }, m_Height{ 0 }, m_VBO{ 0 }, m_VAO{ 0 }, m_Program{ 0 }, m_MenuProgram{ 0 }, m_Texture{ 0 }
{};

void Renderer::Init(int width, int height) 
{
	m_Width = width;
	m_Height = height;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(s_Vertices), s_Vertices, GL_DYNAMIC_DRAW);
	
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &s_VertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &s_FragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	m_Program = glCreateProgram();
	glAttachShader(m_Program, vertexShader);
	glAttachShader(m_Program, fragmentShader);
	glLinkProgram(m_Program);

	glUseProgram(m_Program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Create second m_Program to load menu frag shader
	m_MenuProgram = glCreateProgram();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &s_VertexShaderSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &s_FragmentShaderSourceMenu, NULL);
	glCompileShader(fragmentShader);

	glAttachShader(m_MenuProgram, vertexShader);
	glAttachShader(m_MenuProgram, fragmentShader);
	glLinkProgram(m_MenuProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//texture
	glGenTextures(2, &m_Texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

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
	glUseProgram(m_Program);
	glm::mat4 model = glm::mat4(1.0f);

	GLint uniformTranslate = glGetUniformLocation(m_Program, "translate");
	glUniformMatrix4fv(uniformTranslate, 1, GL_FALSE, glm::value_ptr(model));

	GLint uniformZoom = glGetUniformLocation(m_Program, "zoom");
	glUniform1f(uniformZoom, (float)zoom);

	GLint uniformPan = glGetUniformLocation(m_Program, "pan");
	glUniform2f(uniformPan, center.x, center.y);

	glUseProgram(m_Program);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::Draw(unsigned char* tex, int posX, int posY, int width, int height, float rotation)
{
	glUseProgram(m_MenuProgram);

	glm::vec2 position = ConvertPixelToNorm(posX, posY);
	glm::vec2 size;
	size.x = (float)width / (float)m_Width;
	size.y = (float)height / (float)m_Height;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));


	GLint uniformTranslate = glGetUniformLocation(m_Program, "translate");
	glUniformMatrix4fv(uniformTranslate, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

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

void Renderer::PrintStatus() const
{
	std::cout << "Texture ID: " << m_Texture << std::endl << "m_VAO: " 
		<< m_VAO << std::endl << "m_VBO: " << m_VBO << std::endl;
}

glm::vec2 Renderer::ConvertNormToPixel(glm::vec2 xy)
{
	float outX = ((xy.x + 1.0f) / 2.0f) * m_Width;
	float outY = ((xy.y + 1.0f) / 2.0f) * m_Height;
	outY = outY * -1; //flip y for drawing

	return glm::vec2(outX, outY);
}

glm::vec2 Renderer::ConvertPixelToNorm(int x, int y)
{
	float outX = (((float)x / (float)m_Width)*2) - 1;
	float outY = (((float)y / (float)m_Height) * 2) - 1;
	outY = outY * -1; //flip y for drawing

	return glm::vec2(outX, outY);
}

