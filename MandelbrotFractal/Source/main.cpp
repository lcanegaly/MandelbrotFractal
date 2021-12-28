#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include "Fractal.h"
#include "glm.hpp"




int main(void)
{

	
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Mandelbrot Fractal Set Viewer", NULL, NULL);
	glfwMakeContextCurrent(window);

	glewInit();

	Fractal fractal(glm::vec2(800.0f, 600.0f), glm::vec2(2.0f, 2.0f));
	fractal.calculate();

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.55f, 0.3f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
	
		fractal.display();

		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}