#pragma once
#include "Renderer.h"
#include "Texture.h"
#include <iostream>

struct mouseInput
{
	double mouseX;
	double mouseY;
	bool leftClick;
	bool rightClick;

	void Clear() { mouseX = 0; mouseY = 0; leftClick = false; rightClick = false; };
};

class Gui
{
public:
	Gui();
	void addMouseInputEvent(int button, int action, double xpos, double ypos);
	bool Button(float width, float height, float posX, float posY);
	void resetGui();
	

private:

	mouseInput mouse;
	Renderer guiRenderer;
	Texture tex;

};

