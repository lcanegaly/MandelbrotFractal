#include "Gui.h"

void Gui::mouse_button_callback(int button, int action, int mods)
{
	this->mouse.leftClick = true;
}

bool Gui::Button(int width, int height, int posx, int posy)
{
	//TODO - if mouse clicked within area of button return true
	if (this->mouse.leftClick)
		return true;
	return false;
}

void Gui::resetGui()
{
	this->mouse.leftClick = false;
}
