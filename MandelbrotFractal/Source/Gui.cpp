#include "Gui.h"

Gui::Gui() 
{
	tex.createTexture(glm::vec2(100, 100));
	for (int x = 0; x < (100 * 100); x++)
	{
		tex.setPixelColor(glm::vec3(3, 252, 207));
	}

	this->guiRenderer.PrintStatus();
}

void Gui::addMouseInputEvent(int button, int action, double xpos, double ypos)
{

	(button == 0 && action == 1) ? mouse.leftClick = true : mouse.leftClick = false;
	(button == 1 && action == 1) ? mouse.rightClick = true : mouse.rightClick = false;
	mouse.mouseX = xpos;
	mouse.mouseY = ypos;

}

bool Gui::Button(int width, int height, int posx, int posy)
{

	guiRenderer.Draw(tex.getTexture(), glm::vec2(100, 100), glm::vec2(100, 100));

	if (this->mouse.leftClick && mouse.mouseX - posx < width && mouse.mouseY - posy < height)
		return true;
	return false;
}

void Gui::resetGui()
{
	mouse.Clear();
}
