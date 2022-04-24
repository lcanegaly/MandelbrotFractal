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
	void line(int x1, int y1, int x2, int y2);
	void arrow(int x, int y, int sizeX, int sizeY);
	glm::vec2 size();

private:
	glm::vec2 texSize;
	unsigned char* pixel = nullptr;
	int pixelPosition = 0;
	long textureSize = 0;
};
