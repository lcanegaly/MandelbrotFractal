#pragma once
#include "glm.hpp"

class Texture 
{
public:

	Texture();
	void create(glm::vec2 size);
	unsigned char* getData();
	void setData(glm::vec3 color);
	void clearData();

private:
	unsigned char* data = nullptr;
	int counter = 0;
};
