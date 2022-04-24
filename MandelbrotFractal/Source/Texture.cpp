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