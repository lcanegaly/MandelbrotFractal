#include "Texture.h"

Texture::Texture()
{

}

void Texture::create(glm::vec2 size)
{
	long dataSize = (int)size.x * (int)size.y;
	dataSize = dataSize * 3;
	this->data = new unsigned char[dataSize];
}

unsigned char* Texture::getData()
{
	return data;
}

void Texture::setData(glm::vec3 color)
{
	data[counter] = color.x;
	++counter;
	data[counter] = color.y;
	++counter;
	data[counter] = color.z;
	++counter;

}

void Texture::clearData()
{
	delete[] data;
}
