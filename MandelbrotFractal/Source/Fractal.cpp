#include "Fractal.h"
#include <iostream>


Fractal::Fractal(glm::vec2 screenSize, glm::vec2 bounds) : screenSize{ screenSize }, bounds{bounds}
{
	texture.create(screenSize);
}

void Fractal::calculate()
{
	

	//Complex point;
	std::complex<double> point;
	
	for (int y = 0; y < 600; y++) 
	{
		for (int x = 0; x < 800; x++) 
		{
			this->translateCoord(&point, x, y);
			std::complex<double> value(0.0,0.0);
			std::complex<double> pt(std::real(point), std::imag(point));
			int iteration = 0;

			while (std::real(value) < 2 && std::imag(value) < 2 && iteration <= 50)
			{
				value = value * value;
				value = value + pt;
				iteration++;
			}
			
			if (iteration >= 40) 
			{
				texture.setData(glm::vec3(255, 0, 0));
			}
			else if(iteration >= 30 && iteration < 40)
			{
				texture.setData(glm::vec3(0, 255, 0));
			}
			else if (iteration >= 20 && iteration < 30)
			{
				texture.setData(glm::vec3(0, 0, 255));
			}
			else if (iteration >= 10 && iteration < 20)
			{
				texture.setData(glm::vec3(0, 100, 100));
			}
			else if (iteration >= 0 && iteration < 10)
			{
				texture.setData(glm::vec3(0, 0, 0));
			}

		}
	}

}

void Fractal::setBounds(glm::vec2 bounds)
{
	this->bounds = bounds;
}

void Fractal::display()
{
	renderer.Draw(texture.getData(), screenSize.x, screenSize.y);
}

void Fractal::translateCoord(std::complex<double>* comp, int x, int y)
{
	std::complex<double> point(*comp);
	long double multiplierx = (this->bounds.x / 800.0);
	long double multipliery = (this->bounds.y / 600.0);

	long double start = this->bounds.x * -0.5;
	comp->real(start + (x * multiplierx));

	start = this->bounds.x * -0.5;
	comp->imag(start + (y * multipliery));

}
