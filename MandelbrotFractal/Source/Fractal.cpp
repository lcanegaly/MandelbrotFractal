#include "Fractal.h"
#include <iostream>


Fractal::Fractal(glm::vec2 screenSize, glm::vec2 centerPoint) : screenSize{ screenSize }, centerPoint{ centerPoint }
{
	this->zoom = 2.0;
	texture.create(screenSize);
}

void Fractal::calculate()
{
	if (this->calculated == false) {
		texture.clearData();
		this->calculated = true;

		//Complex point;
		std::complex<double> point;

		for (int y = 0; y < 600; y++)
		{
			for (int x = 0; x < 800; x++)
			{
				this->translateCoord(&point, x, y);
				std::complex<double> value(0.0, 0.0);
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
				else if (iteration >= 30 && iteration < 40)
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
}

void Fractal::setBounds(glm::vec2 centerPoint, double zoom)
{
	
	this->calculated = false;

	this->centerPoint += centerPoint * glm::vec2(this->zoom, this->zoom);
	if (zoom > 0)
	{
		this->zoom = this->zoom / 2;
	}
	if (zoom < 0)
	{
		this->zoom = this->zoom * 2;
	}

	std::cout << "Zoom : " << this->zoom << std::endl;
	
}


void Fractal::display()
{
	renderer.Draw(texture.getData(), screenSize.x, screenSize.y);
}

void Fractal::translateCoord(std::complex<double>* comp, int x, int y)
{
	std::complex<double> point(*comp);
	long double multiplierx = (this->zoom / 800.0);
	long double multipliery = (this->zoom / 600.0);

	long double start = this->zoom * -0.5 + this->centerPoint.x;
	comp->real(start + (x * multiplierx));

	start = this->zoom * -0.5 + this->centerPoint.y;
	comp->imag(start + (y * multipliery));

}
