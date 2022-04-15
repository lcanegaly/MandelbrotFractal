#include "Fractal.h"
#include <iostream>
#include <chrono>


Fractal::Fractal(glm::vec2 screenSize, glm::vec2 centerPoint) : screenSize{ screenSize }, centerPoint{ centerPoint }
{
	this->zoom = 2.0;

}


void Fractal::setBounds(glm::vec2 centerPoint, double zoom)
{
	
	this->calculated = false;

	this->centerPoint += centerPoint * glm::vec2(this->zoom, this->zoom);
	if (zoom > 0)
	{
		this->zoom = this->zoom / 1.1;
	}
	if (zoom < 0)
	{
		this->zoom = this->zoom * 1.1;
	}
}


void Fractal::display()
{
	renderer->DrawFractal(screenSize.x, screenSize.y, centerPoint, zoom);
}

void Fractal::translateCoord(std::complex<double>* comp, int x, int y)
{
	std::complex<double> point(*comp);
	long double multiplierx = (this->zoom / this->screenSize.x);
	long double multipliery = (this->zoom / this->screenSize.y);

	long double start = this->zoom * -0.5 + this->centerPoint.x;
	comp->real(start + (x * multiplierx));

	start = this->zoom * -0.5 + this->centerPoint.y;
	comp->imag(start + (y * multipliery));

}
