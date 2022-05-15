#pragma once
#include "glm.hpp"
#include "Renderer.h"
#include "Texture.h"
#include <complex>

class Fractal 
{
public:

	Fractal(glm::vec2 screenSize, glm::vec2 centerPoint, Renderer& renderer);

	//sets the coordinate plane bounds
	void setBounds(glm::vec2 centerPoint, double zoom);

	void display();

	//Renderer* renderer;
	Renderer& renderer;
private:
	glm::vec2 centerPoint;
	double zoom;
	double iterationLimit = 500;
	glm::vec2 screenSize;
	
	//Texture texture;
	bool calculated = false;
};