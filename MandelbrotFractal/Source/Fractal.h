#pragma once
#include "glm.hpp"
#include "Renderer.h"
#include "Texture.h"
#include <complex>

class Fractal 
{
public:

	

	Fractal(glm::vec2 screenSize, glm::vec2 bounds);
	void calculate();

	//sets the coordinate plane bounds
	void setBounds(glm::vec2 bounds);

	void display();

	//takes pixel location and converts to point within drawing bounds
	void translateCoord(std::complex<double>* comp, int x, int y);

private:
	glm::vec2 bounds;
	glm::vec2 screenSize;
	Renderer renderer;
	Texture texture;

};