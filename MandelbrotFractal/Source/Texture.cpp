#include "Texture.h"

Texture::Texture()
{

}

void Texture::createTexture(glm::vec2 size)
{
	this->textureSize = (int)size.x * (int)size.y;
	textureSize = textureSize * 3;
	this->pixel = new unsigned char[textureSize];
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

void Texture::clearTexture()
{
	delete[] pixel;
	this->pixel = new unsigned char[textureSize];
	this->pixelPosition = 0;
}
