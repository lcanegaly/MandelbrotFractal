#pragma once


struct mouseInput
{
	int mouseX;
	int mouseY;
	bool leftClick;
	bool rightClick;
};

class Gui
{
public:
	
	void mouse_button_callback(int button, int action, int mods);
	bool Button(int width, int height, int posX, int posY);
	void resetGui();

private:

	mouseInput mouse;

};

