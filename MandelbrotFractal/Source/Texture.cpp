#include "Texture.h"
#include <iostream>

Texture::Texture()
{


}

void Texture::createTexture(glm::vec2 size)
{
	this->textureSize = (int)size.x * (int)size.y;
	textureSize = textureSize * 3;
	this->pixel = new unsigned char[textureSize];
	this->texSize = size;
}

unsigned char* Texture::getTexture()
{
	return pixel;
}

void Texture::setPixelColor(glm::vec3 color)
{
	//set red value
	pixel[pixelPosition] = color.x;
	++pixelPosition;
	//set green value
	pixel[pixelPosition] = color.y;
	++pixelPosition;
	//set blue value
	pixel[pixelPosition] = color.z;
	++pixelPosition;

}

void Texture::setPixelColor(glm::vec2 pos, glm::vec3 color)
{
	int position = 3 * (pos.x + pos.y * int(this->texSize.x));
	pixel[position] = color.x;
	pixel[position + 1] = color.y;
	pixel[position + 2] = color.z;
}

glm::vec3 Texture::getPixelColor(glm::vec2 pos)
{
	glm::vec3 color{0.0f, 0.0f, 0.0f};
	int position = 3 * (pos.x + pos.y * int(this->texSize.x));
	
	int x = pixel[position];
	int y = pixel[position + 1];
	int z =	pixel[position + 2];

	color = glm::vec3(x, y, z);



	return color;
}

void Texture::line(int x1, int y1, int x2, int y2){
	
	float slope = 0.0f;

	if (x1!=x2){
		slope = (float(y1-y2))/(float(x1-x2));
	}else{
		int ity = (y1 > y2) ? y2 : y1;
		for (int y = 0; y < abs(y1-y2); ++y){
			int x = x1;
			int position = 3*(x+((ity+y)*int(this->texSize.x)));
			pixel[position-1]= 100.0f;
			pixel[position]= 100.0f;
			pixel[position+1]= 100.0f;
		}
		return;
	}
	
	if (y2 == y1){
		int itx = (x1 > x2) ? x2 : x1;
		for (int x = 0; x < abs(x1 - x2); ++x) {
			int y = y1;
			int position = 3 * (itx+x + (y * int(this->texSize.x)));
			pixel[position - 1] = 100.0f;
			pixel[position] = 100.0f;
			pixel[position + 1] = 100.0f;
		}
		return;
	}
		
	int itx = 0, ity = 0;

	if (slope > 0) {
		if (x1 > x2)
			itx = x2, ity = y2;
		else
			itx = x1, ity = y1;
	}
	else if(slope < 0) {
		if (x1 > x2)
			itx = x2, ity = y1;
		else
			itx = x1, ity = y2;
	}

	float b = y1 - (slope * x1);
	
	for (int x = 0; x < abs(x1-x2); ++x){
		int y = slope*(itx+x)+b;
		int position = 3*((itx+x)+(y*int(this->texSize.x)));
		pixel[position-1]= 100.0f;
		pixel[position]= 100.0f;
		pixel[position+1]= 100.0f;
	}
	
	for (int y = 0; y < abs(y1-y2); ++y){
		int x = ((ity+y)-b)/slope;
		int position = 3*(x+((ity+y)*int(this->texSize.x)));
		pixel[position-1]= 100.0f;
		pixel[position]= 100.0f;
		pixel[position+1]= 100.0f;
	}
}


void Texture::arrow(int x, int y, int sizeX, int sizeY){


	line(x - sizeX/2, y-sizeY, x, y);
	line(x + sizeX/2, y - sizeY, x, y);
	line(x + sizeX / 2, y - sizeY, x - sizeX / 2, y - sizeY);

	floodFill(glm::vec2(x, y - y * 0.5), glm::vec3(10, 10, 10), glm::vec3(getPixelColor(glm::vec2(x, y - y * 0.5))));

}

//needs some rethinking..
void Texture::floodFill(glm::vec2 pos, glm::vec3 color, glm::vec3 match)
{
	//fill lines below starting pixel
	int posY = pos.y;
	glm::vec3 pcolor = getPixelColor(glm::vec2(pos.x, posY));
	while (pcolor == match) {

		
		int posX = pos.x - 1;
		glm::vec3 xcolor = getPixelColor(glm::vec2(posX, posY));
		while (xcolor == match) {
			if (posX > 0) {
				setPixelColor(glm::vec2(posX, posY), color);
				posX -= 1;
				xcolor = getPixelColor(glm::vec2(posX, posY));
			}
		}
		
		posX = pos.x + 1;
		xcolor = getPixelColor(glm::vec2(posX, posY));
		while (xcolor == match) {
			if (posX < texSize.x) {
				setPixelColor(glm::vec2(posX, posY), color);
				posX += 1;
				xcolor = getPixelColor(glm::vec2(posX, posY));
			}
		}

		if (posY > 0) {
			setPixelColor(glm::vec2(pos.x, posY), color);
			posY -= 1;
			pcolor = getPixelColor(glm::vec2(pos.x, posY));
		}

	}
	
	//fill lines above starting pixel
	posY = pos.y;
	pcolor = getPixelColor(glm::vec2(pos.x, posY + 1 ));
	while (pcolor == match) {
		int posX = pos.x + 1;
		glm::vec3 xcolor = getPixelColor(glm::vec2(posX, posY));
		while (xcolor == match) {
			if (posX < texSize.x) {
				setPixelColor(glm::vec2(posX, posY), color);
				posX += 1;
				xcolor = getPixelColor(glm::vec2(posX, posY));
			}
		}
		posX = pos.x - 1;
		xcolor = getPixelColor(glm::vec2(posX, posY));
		while (xcolor == match) {
			if (posX < texSize.x) {
				setPixelColor(glm::vec2(posX, posY), color);
				posX -= 1;
				xcolor = getPixelColor(glm::vec2(posX, posY));
			}
		}
		if (posY < texSize.y) {
			setPixelColor(glm::vec2(pos.x, posY), color);
			posY += 1;
			pcolor = getPixelColor(glm::vec2(pos.x, posY));
		}
	}
}

void Texture::clearTexture()
{
	delete[] pixel;
	this->pixel = new unsigned char[textureSize];
	this->pixelPosition = 0;
}

glm::vec2 Texture::size(){

	return this->texSize;
}