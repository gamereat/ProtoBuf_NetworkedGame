#include "UIButton.h"

#include "GameLogging.h"
 
UIButton::UIButton(sf::Vector2f buttonSize, sf::Vector2f location, const char * textureFileName, sf::Window* window)
{
	this->window = window;
	if (!buttonTexture.loadFromFile(textureFileName))
	{
		GameLogging::LogError("Failed to load in paddle texture");
	}
	else
	{
		buttonShape.setTexture(&buttonTexture);

 	}
	buttonShape.setPosition(location);
	buttonShape.setSize(buttonSize);
}


UIButton::~UIButton()
{
}

void UIButton::Render(sf::RenderWindow * renderWindow)
{
	renderWindow->draw(buttonShape);
}

bool UIButton::HasButtonBeenPressed(sf::Vector2i mousePos)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{


		// Check if button overlaps with the mouse
		if (buttonShape.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
		{
			return true;
		}
 
 
	}
	return false;
}

 