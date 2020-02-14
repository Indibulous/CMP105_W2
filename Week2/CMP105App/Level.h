#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput();
	void update();
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	std::string mousePosDisplay;
	std::string mouseDragDisplay;
	sf::Vector2f mouseClickPos;
	sf::Vector2f mouseReleasePos;
	sf::Vector2f dragLength;
	float dragMagnitude;
	float colorFade;
	bool clickStart;
	bool clickEnd;

	// Add your object here
	sf::Font font;
	sf::Text txt_mousePos;
	sf::Text txt_mouseDrag;
	sf::Vertex line_mouseDrag[2];
};