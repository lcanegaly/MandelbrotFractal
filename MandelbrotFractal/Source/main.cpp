#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include "Fractal.h"
#include "glm.hpp"
#include <iostream>




//static void scroll_callback(GLFWwindow*, double, double);
static void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);


Fractal* fractal_ptr = nullptr;
GLFWwindow* window = nullptr;

int main(void)
{
	
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(400, 300, "Mandelbrot Fractal Set Viewer", NULL, NULL);
	glfwMakeContextCurrent(window);

	
	//glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);


	glewInit();

	Fractal fractal(glm::vec2(400.0f, 300.0f), glm::vec2(0.0f, 0.0f));
	fractal_ptr = &fractal; 
	fractal.calculate();

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.55f, 0.3f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		fractal.calculate();
		fractal.display();
	

		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		fractal_ptr->setBounds(glm::vec2(-0.1, 0.0), 0);
	
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		fractal_ptr->setBounds(glm::vec2(0.1, 0.0), 0);

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		fractal_ptr->setBounds(glm::vec2(0.0, 0.1), 0);

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		fractal_ptr->setBounds(glm::vec2(0.0, -0.1), 0);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		fractal_ptr->setBounds(glm::vec2(0.0, 0.0), -0.1);
	
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
		fractal_ptr->setBounds(glm::vec2(0.0, 0.0), 0.1);

}

/*
static void scroll_callback(GLFWwindow*, double xoffset, double yoffset) 
{

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	std::cout << xoffset << " : " << yoffset << std::endl;
	std::cout << xpos << " : " << ypos << std::endl;
	std::complex<double> point;
	fractal_ptr->translateCoord(&point, xpos, ypos);

	fractal_ptr->setBounds(glm::vec2(std::real(point), std::imag(point)), yoffset);

}
*/