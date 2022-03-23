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
	bool Button(int width, int height, int posX, int posY, int texture);
	void resetGui();
	Renderer* guiRenderer;

private:
	bool drawn = false;
	mouseInput mouse;
	Texture tex;
	Texture tex2;
	Texture tex3;
};

