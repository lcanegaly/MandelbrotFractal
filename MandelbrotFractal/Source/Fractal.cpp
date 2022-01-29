#include "Fractal.h"
#include <iostream>
#include <chrono>


Fractal::Fractal(glm::vec2 screenSize, glm::vec2 centerPoint) : screenSize{ screenSize }, centerPoint{ centerPoint }
{
	this->zoom = 2.0;
	texture.create(screenSize);
}

void Fractal::calculate()
{
	if (this->calculated == false) {
		auto t1 = std::chrono::high_resolution_clock::now();
		texture.clearData();
		this->calculated = true;

		//Complex point;
		std::complex<double> point;

		for (int y = 0; y < this->screenSize.y; y++)
		{
			for (int x = 0; x < this->screenSize.x; x++)
			{
				this->translateCoord(&point, x, y);
				std::complex<double> value(0.0, 0.0);
				std::complex<double> pt(std::real(point), std::imag(point));
				int iteration = 0;

				this->iterationLimit = 1 / this->zoom * 40;
				while (std::real(value) + std::imag(value) < 4 && iteration <= this->iterationLimit)
				{
					
					value = value * value;
					value = value + pt;
					iteration++;
				}

				texture.setData(glm::vec3((2 * iteration), iteration, (255 - 2 * iteration)));

			}
		}

		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> ms_int = t2 - t1;
		std::cout << "Calculation Time S: " << ms_int.count() / 1000 << " Zoom : " << this->zoom << std::endl;
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
}


void Fractal::display()
{
	renderer.Draw(texture.getData(), screenSize.x, screenSize.y);
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
