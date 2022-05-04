#include "Gui.h"
#include <cmath>

Gui::Gui() 
{
	
	this->resetGui();

}

void Gui::addMouseInputEvent(int button, int action, double xpos, double ypos)
{

	(button == 0 && action == 1) ? mouse.leftClick = true : mouse.leftClick = false;
	(button == 1 && action == 1) ? mouse.rightClick = true : mouse.rightClick = false;
	mouse.mouseX = xpos;
	mouse.mouseY = ypos;

}

bool Gui::Button(int width, int height, int posX, int posY, int texture)
{
	if (!drawn)
	{
		drawn = true;
		tex[texture].createTexture(glm::vec2(width, height));
		for (int x = 0; x < (width * height); x++)
		{
			tex[texture].setPixelColor(glm::vec3(0, 255, 0));
		}
		tex[texture].arrow(width/2, height-(height/4), width / 2, height / 2);
		
	}

	guiRenderer->Draw(tex[texture].getTexture(), posX, posY, width, height);


	if (this->mouse.leftClick) {

		
		int x = std::abs(mouse.mouseX - posX);
		int y = std::abs(mouse.mouseY - posY);


		if ( (x <= 0.5 * width) && ( y <= 0.5 * height ))
		{
			return true;
		}
			
	}

	return false;
}

void Gui::resetGui()
{
	drawn = false;
	mouse.Clear();
	tex[0].clearTexture();

}

