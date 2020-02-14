#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	
	//Mouse Position Indicator
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}
	txt_mousePos.setFont(font);
	txt_mousePos.setPosition(0, 0);
	txt_mousePos.setCharacterSize(24);
	txt_mousePos.setFillColor(sf::Color(255, 255, 255, 255));

	//Mouse Drag Length Indicator
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}
	txt_mouseDrag.setFont(font);
	txt_mouseDrag.setPosition(0, 0);
	txt_mouseDrag.setCharacterSize(24);
	txt_mouseDrag.setFillColor(sf::Color(255, 255, 255, 0));

	clickStart = false;
	clickEnd = false;

	dragMagnitude = 0;

	//Mouse Drag Line
	line_mouseDrag[0].color = sf::Color(255, 255, 255, 0);
	line_mouseDrag[1].color = sf::Color(255, 255, 255, 0);

	colorFade = 0;

}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	// output to console if W is pressed output to console
	if (input->isKeyDown(sf::Keyboard::W))
	{
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "W was pressed\n";
	}

	// output to console if J, K and L are pressed together
	if (input->isKeyDown(sf::Keyboard::J) && input->isKeyDown(sf::Keyboard::K) && input->isKeyDown(sf::Keyboard::L))
	{
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
		std::cout << "J, K and L were pressed together\n";
	}

	if (input->isMouseLDown() == true)
	{
		if (clickStart == false)
		{
		mouseClickPos = sf::Vector2f((float)input->getMouseX(), (float)input->getMouseY());
		clickStart = true;
		}
		clickEnd = false;
		line_mouseDrag[0].color = sf::Color(0, 255, 255, 255);
		line_mouseDrag[1].color = sf::Color(255, 0, 255, 255);
		txt_mouseDrag.setFillColor(sf::Color(255, 255, 255, 180));
		//std::cout << "click!\n";
		mouseReleasePos = sf::Vector2f((float)input->getMouseX(), (float)input->getMouseY());
	}
	else
	{
		if (clickEnd == false && clickStart == true)
		{
			mouseReleasePos = sf::Vector2f((float)input->getMouseX(), (float)input->getMouseY());
			clickEnd = true;
			colorFade = 255;
			std::cout << "Line Length: " << dragMagnitude << " pixels\n";
		}
		clickStart = false;

		if (colorFade > 0)
		{
		colorFade -= 0.02f;
		}
		line_mouseDrag[0].color = sf::Color((int)(colorFade + 0.5f)/2, 255, 255, (int)(colorFade + 0.5f));
		line_mouseDrag[1].color = sf::Color(255, (int)(colorFade + 0.5f) / 2, 255, (int)(colorFade + 0.5f));
		txt_mouseDrag.setFillColor(sf::Color(255, 255, 255, (int)(colorFade + 0.5f)));
	}
}

// Update game objects
void Level::update()
{
	//Mouse Position Indicator
	mousePosDisplay = (std::to_string(std::max(input->getMouseX(), 0)) + ", " + std::to_string(std::max(input->getMouseY(), 0)));
	txt_mousePos.setString(mousePosDisplay);

	//Mouse Drag Length Indicator
	dragLength = mouseReleasePos - mouseClickPos;
	mouseDragDisplay = (std::to_string((int)dragLength.x) + ", " + std::to_string((int)dragLength.y));
	txt_mouseDrag.setString(mouseDragDisplay);
	txt_mouseDrag.setPosition(sf::Vector2f(mouseReleasePos));
	line_mouseDrag[0].position = sf::Vector2f(mouseClickPos);
	line_mouseDrag[1].position = sf::Vector2f(mouseReleasePos);
	dragMagnitude = (int)hypot((dragLength.x), (dragLength.y));

}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(line_mouseDrag, 2, sf::Lines);
	window->draw(txt_mousePos);
	window->draw(txt_mouseDrag);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(0, 0, 0));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}