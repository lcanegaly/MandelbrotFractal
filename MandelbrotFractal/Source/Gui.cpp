#include "Gui.h"

void Gui::mouse_button_callback(int button, int action, double xpos, double ypos)
{

	(button == 0 && action == 1) ? mouse.leftClick = true : mouse.leftClick = false;
	(button == 1 && action == 1) ? mouse.rightClick = true : mouse.rightClick = false;
	mouse.mouseX = xpos;
	mouse.mouseY = ypos;

}

bool Gui::Button(int width, int height, int posx, int posy)
{
	if (this->mouse.leftClick && mouse.mouseX - posx < width && mouse.mouseY - posy < height)
		return true;
	return false;
}

void Gui::resetGui()
{
	this->mouse.leftClick = false;
	this->mouse.mouseX = 0;
	this->mouse.mouseY = 0;
}
