#include "Gui.h"
#include <cmath>

Gui::Gui(Renderer& rend): guiRenderer { rend }
{
	this->resetGui();
	for (int i = 0; i < this->numTextures; ++i) {
		tex[i].createTexture(glm::vec2(defaultWidth, defaultHeight));
		for (int x = 0; x < (defaultWidth * defaultHeight); x++)
		{
			tex[i].setPixelColor(glm::vec3(0, 255, 0));
		}
	}
	//create button textures to be used with Gui object
	//up arrow
	tex[Icons::up_arrow].arrow(defaultWidth / 2, defaultHeight - (defaultHeight / 4), defaultWidth / 2, defaultHeight / 2);
	//down arrow
	tex[Icons::down_arrow].arrow(defaultWidth / 2, defaultHeight - (defaultHeight / 4), defaultWidth / 2, defaultHeight / 2);
	tex[Icons::down_arrow].setRotation(180.0f);
	//left arrow
	tex[Icons::left_arrow].arrow(defaultWidth / 2, defaultHeight - (defaultHeight / 4), defaultWidth / 2, defaultHeight / 2);
	tex[Icons::left_arrow].setRotation(90.0f);
	//right arrow
	tex[Icons::right_arrow].arrow(defaultWidth / 2, defaultHeight - (defaultHeight / 4), defaultWidth / 2, defaultHeight / 2);
	tex[Icons::right_arrow].setRotation(-90.0f);
	//minus
	tex[Icons::minus].minus(defaultWidth / 2, defaultHeight - (defaultHeight / 2), defaultWidth / 2, defaultHeight / 2);
	//plus
	tex[Icons::plus].plus(defaultWidth / 2, defaultHeight - (defaultHeight / 2), defaultWidth / 2, defaultHeight / 2);
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

bool Gui::Button(int width, int height, int posX, int posY, int texture, float rotation)
{
	guiRenderer.Draw(tex[texture].getTexture(), posX, posY, width, height, tex[texture].getRotation());

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

