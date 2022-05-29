#include "Window.h"
#include "Renderer.h"
#include "Fractal.h"
#include "glm.hpp"
#include "Gui.h"
#include "MouseInput.h"

#define WIDTH 1100
#define HEIGHT 900


int main(void)
{
	Window::Create(WIDTH, HEIGHT);

	Renderer& renderer = Renderer::Get();
	Renderer::Get().Init(WIDTH, HEIGHT);

	Fractal fractal(glm::vec2(WIDTH, HEIGHT), glm::vec2(-0.5f, 0.0f), renderer);

	MouseInput mouse;
	Gui gui(renderer);


	//while (!glfwWindowShouldClose(window))
	while (!Window::ShouldClose())
	{
		Window::Clear();

		fractal.Display();

		//up button
		if (gui.Button(40, 40, 80, 80, gui.up_arrow)) 
		{
			fractal.SetBounds(glm::vec2(0.0, 0.1), 0);
		}
		//down button
		if (gui.Button(40, 40, 80, 180, gui.down_arrow))
		{
			fractal.SetBounds(glm::vec2(0.0, -0.1), 0);
		}
		//left button
		if (gui.Button(40, 40, 40, 130, gui.left_arrow))
		{
			fractal.SetBounds(glm::vec2(-0.1, 0.0), 0);
		}
		//right button
		if (gui.Button(40, 40, 120, 130, gui.right_arrow))
		{
			fractal.SetBounds(glm::vec2(0.1, 0.0), 0);
		}
		//zoom in button
		if (gui.Button(40, 40, 160, 80, gui.plus))
		{
			fractal.SetBounds(glm::vec2(0.0, 0.0), 0.1);
		}
		//zoom out button
		if (gui.Button(40, 40, 160, 180, gui.DrawMinus))
		{
			fractal.SetBounds(glm::vec2(0.0, 0.0), -0.1);
		}
		gui.ResetGui();

		Window::GetMouseInput(mouse);
		gui.AddMouseInputEvent(mouse);
	}

	Window::Close();

	return 0;
}
