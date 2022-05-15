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
	Gui(Renderer& rend);
	~Gui();
	int defaultWidth = 40;
	int defaultHeight = 40;
	void addMouseInputEvent(int button, int action, double xpos, double ypos);
	bool Button(int width, int height, int posX, int posY, int texture);
	void resetGui();
	Renderer& guiRenderer;

private:
	
	bool drawn = false;
	mouseInput mouse;
	Texture tex[6];
};

