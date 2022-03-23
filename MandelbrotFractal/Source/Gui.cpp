#include "Gui.h"
#include <cmath>

Gui::Gui() 
{
	/*
	//1200, 1000 window size
	tex.createTexture(glm::vec2(100, 100));
	for (int x = 0; x < (100 * 100); x++)
	{
		tex.setPixelColor(glm::vec3(255, 0, 0));
	}

	tex2.createTexture(glm::vec2(100, 100));
	for (int x = 0; x < (100 * 100); x++)
	{
		tex2.setPixelColor(glm::vec3(0, 255, 0));
	}
	tex3.createTexture(glm::vec2(100, 100));
	for (int x = 0; x < (100 * 100); x++)
	{
		tex3.setPixelColor(glm::vec3(0, 0, 255));
	}
	*/
	this->resetGui();
	//this->guiRenderer->PrintStatus();
}

void Gui::addMouseInputEvent(int button, int action, double xpos, double ypos)
{

	(button == 0 && action == 1) ? mouse.leftClick = true : mouse.leftClick = false;
	(button == 1 && action == 1) ? mouse.rightClick = true : mouse.rightClick = false;
	mouse.mouseX = xpos;
	mouse.mouseY = ypos;

}

bool Gui::Button(int width, int height, int posX, int posY, int texure)
{
	if (!drawn)
	{
		drawn = true;
		tex.createTexture(glm::vec2(width, height));
		for (int x = 0; x < (width * height); x++)
		{
			tex.setPixelColor(glm::vec3(255, 0, 0));
		}

		tex2.createTexture(glm::vec2(width, height));
		for (int x = 0; x < (width * height); x++)
		{
			tex2.setPixelColor(glm::vec3(0, 255, 0));
		}
		tex3.createTexture(glm::vec2(width, height));
		for (int x = 0; x < (width * height); x++)
		{
			tex3.setPixelColor(glm::vec3(0, 0, 255));
		}

	}
	//convert pixel to normalized to pass to draw call.

	if (texure == 1) {
		//guiRenderer->Draw(tex.getTexture(), glm::vec2(posX, posY), glm::vec2(width, height));
		guiRenderer->Draw(tex.getTexture(), posX, posY, width, height);
	}
	if (texure == 2) {
		//guiRenderer->Draw(tex2.getTexture(), glm::vec2(posX, posY), glm::vec2(width, height));
		guiRenderer->Draw(tex2.getTexture(), posX, posY, width, height);
	}
	if (texure == 3) {
		//guiRenderer->Draw(tex3.getTexture(), glm::vec2(posX, posY), glm::vec2(width, height));
		guiRenderer->Draw(tex3.getTexture(), posX, posY, width, height);
	}



	if (this->mouse.leftClick) {

		
		int x = std::abs(mouse.mouseX - posX);
		int y = std::abs(mouse.mouseY - posY);

		/*
		printf("Mouse pos is X:%f Y:%f \n", mouse.mouseX, mouse.mouseY);
		printf("Mouse offset is X:%d Y:%d \n", x, y);
		printf("Mouse Box is X:%d Y:%d \n", posX, posY);
		*/

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
	tex.clearTexture();
	tex2.clearTexture();
	tex3.clearTexture();
}

