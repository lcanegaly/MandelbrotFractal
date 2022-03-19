#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include "Fractal.h"
#include "glm.hpp"
#include <iostream>
#include "Gui.h"

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);

Fractal* fractal_ptr = nullptr;
GLFWwindow* window = nullptr;
Gui* gui_ptr = nullptr;

int main(void)
{
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1200, 1000, "Mandelbrot Fractal Set Viewer", NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glewInit();

	Fractal fractal(glm::vec2(1200.0f, 1000.0f), glm::vec2(-0.5f, 0.0f));
	fractal_ptr = &fractal; 
	fractal.calculate();

	Gui gui;
	gui_ptr = &gui;

	Gui gui2;
	

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.55f, 0.3f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		fractal.calculate();
		fractal.display();

		//test gui button
		if (gui.Button(0.1f, 0.1f, -0.5f, 0.1f))
			std::cout << "mouse click" << std::endl;
		gui.resetGui();

		if (gui2.Button(0.1f, 0.1f, -0.5f, -0.25f))
			std::cout << "mouse click" << std::endl;
		gui2.resetGui();
		
		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		gui_ptr->addMouseInputEvent(0, 1, xpos, ypos);
	}
	
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		gui_ptr->addMouseInputEvent(1, 1, xpos, ypos);
	}

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
