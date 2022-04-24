#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include "Fractal.h"
#include "glm.hpp"
#include <iostream>
#include "Gui.h"

#define WIDTH 1100
#define HEIGHT 900

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

	window = glfwCreateWindow(WIDTH, HEIGHT, "Mandelbrot Fractal Set Viewer", NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glewInit();

	Renderer renderer(WIDTH, HEIGHT);

	Fractal fractal(glm::vec2(WIDTH, HEIGHT), glm::vec2(-0.5f, 0.0f));
	fractal.renderer = &renderer;
	fractal_ptr = &fractal; 


	Gui gui;
	gui_ptr = &gui;
	gui.guiRenderer = &renderer;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.55f, 0.3f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		fractal.display();
		
		if (gui.Button(440, 440, 280, 280, 0)) 
		{
			fractal.setBounds(glm::vec2(0.0, 0.1), 0); //up
		}
/*
		//up button
		if (gui.Button(440, 440, 80, 80, 0)) 
		{
			std::cout << "mouse click" << std::endl;
			fractal.setBounds(glm::vec2(0.0, 0.1), 0); //up
		}

		//down button
		if (gui.Button(40, 40, 80, 180, 0))
		{
			std::cout << "mouse click" << std::endl;
			fractal.setBounds(glm::vec2(0.0, -0.1), 0); //down
		}

		//left button
		if (gui.Button(40, 40, 40, 130, 0))
		{
			std::cout << "mouse click" << std::endl;
			fractal.setBounds(glm::vec2(-0.1, 0.0), 0);//left
		}
		//right button
		if (gui.Button(40, 40, 120, 130, 0))
		{
			std::cout << "mouse click" << std::endl;
			fractal.setBounds(glm::vec2(0.1, 0.0), 0); //right
		}
		//zoom out button
		if (gui.Button(40, 40, 160, 80, 0))
		{
			std::cout << "mouse click" << std::endl;
			fractal.setBounds(glm::vec2(0.0, 0.0), 0.1);//Zoom in
			
		}
		//zoom in button
		if (gui.Button(40, 40, 160, 180, 0))
		{
			std::cout << "mouse click" << std::endl;
			fractal.setBounds(glm::vec2(0.0, 0.0), -0.1);//Zoom in
			
		}
*/
		gui.resetGui();


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
		fractal_ptr->setBounds(glm::vec2(-0.1, 0.0), 0);//left
	
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		fractal_ptr->setBounds(glm::vec2(0.1, 0.0), 0); //right

	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		fractal_ptr->setBounds(glm::vec2(0.0, 0.1), 0); //up

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		fractal_ptr->setBounds(glm::vec2(0.0, -0.1), 0); //down

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) 
		fractal_ptr->setBounds(glm::vec2(0.0, 0.0), -0.1);//Zoom out
	
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) 
		fractal_ptr->setBounds(glm::vec2(0.0, 0.0), 0.1);//Zoom in

}
