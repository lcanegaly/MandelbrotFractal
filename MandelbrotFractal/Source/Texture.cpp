#include "Texture.h"

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

void Texture::line(int x1, int y1, int x2, int y2){

	float slope = 0.0f;
	if (x1!=x2){
		slope = (float(y1-y2))/(float(x1-x2));
	}else{
		for (int y = 0; y < abs(y1-y2); ++y){
			int x = x1;
			int position = 3*(x+((y1+y)*int(this->texSize.x)));
			pixel[position-1]= 100.0f;
			pixel[position]= 100.0f;
			pixel[position+1]= 100.0f;
		}
		return;
	}
		
	
	float b = y1-(slope*x1);

	for (int x = 0; x < abs(x1-x2); ++x){
		int y = slope*(x1+x)+b;
		int position = 3*((x1+x)+(y*int(this->texSize.x)));
		pixel[position-1]= 100.0f;
		pixel[position]= 100.0f;
		pixel[position+1]= 100.0f;
	}

	for (int y = 0; y < abs(y1-y2); ++y){
		
		int x = ((y1+y)-b)/slope;

		int position = 3*(x+((y1+y)*int(this->texSize.x)));
		pixel[position-1]= 100.0f;
		pixel[position]= 100.0f;
		pixel[position+1]= 100.0f;
	}

}


void Texture::arrow(int x, int y, int sizeX, int sizeY){

	line(80, 10, 100, 100);

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