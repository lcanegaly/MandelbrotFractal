#pragma once
#include "Renderer.h"
#include "Texture.h"
#include <iostream>

struct MouseInput
{
	double m_MouseX;
	double m_MouseY;
	bool m_LeftClick;
	bool m_RightClick;

	MouseInput() 
		: m_MouseX{ 0 }, m_MouseY{ 0 }, m_LeftClick{ false }, m_RightClick{ false }{};
	void Clear(){ m_MouseX = 0; m_MouseY = 0; m_LeftClick = false; m_RightClick = false; };
};

class Gui
{
public:
	Gui(Renderer& renderer);
	~Gui();

	void AddMouseInputEvent(int button, int action, double xpos, double ypos);
	bool Button(int width, int height, int posX, int posY, int texture, float rotation = 0);
	void ResetGui();
	enum Icons {up_arrow, down_arrow, left_arrow, right_arrow, DrawMinus, plus};

private:
	Renderer& m_GuiRenderer;
	const static int m_NumTextures = 6;
	bool m_IsDrawn = false;
	MouseInput m_Mouse;
	Texture m_Textures[m_NumTextures];
	int m_DefaultWidth;
	int m_DefaultHeight;
};

