#pragma once


struct mouseInput
{
	double mouseX;
	double mouseY;
	bool leftClick;
	bool rightClick;
};

class Gui
{
public:
	
	void mouse_button_callback(int button, int action, double xpos, double ypos);
	bool Button(int width, int height, int posX, int posY);
	void resetGui();

private:

	mouseInput mouse;

};

