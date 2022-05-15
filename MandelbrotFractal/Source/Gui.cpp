#include "Gui.h"
#include <cmath>

Gui::Gui(Renderer& rend): guiRenderer { rend }
{
	this->resetGui();
	for (int i = 0; i < 3; ++i) {
		tex[i].createTexture(glm::vec2(defaultWidth, defaultHeight));
		for (int x = 0; x < (defaultWidth * defaultHeight); x++)
		{
			tex[i].setPixelColor(glm::vec3(0, 255, 0));
		}
	}
	tex[0].arrow(defaultWidth / 2, defaultHeight - (defaultHeight / 4), defaultWidth / 2, defaultHeight / 2);
	tex[1].arrow(defaultWidth / 2, defaultHeight - 2*(defaultHeight / 4), defaultWidth / 2, defaultHeight / 2);
}

Gui::~Gui()
{
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
	guiRenderer.Draw(tex[texture].getTexture(), posX, posY, width, height);

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
	//tex[0].clearTexture();
}

