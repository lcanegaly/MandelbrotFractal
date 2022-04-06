#pragma once
#include "glm.hpp"

class Texture 
{
public:

	Texture();
	void createTexture(glm::vec2 size);
	unsigned char* getTexture();
	void setPixelColor(glm::vec3 color);
	void clearTexture();

private:
	unsigned char* pixel = nullptr;
	int pixelPosition = 0;
	long textureSize = 0;
};
