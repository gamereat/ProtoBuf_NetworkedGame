#include "UIButton.h"

#include "GameLogging.h"
 
UIButton::UIButton(sf::Vector2f buttonSize, sf::Vector2f location, const char * textureFileName)
{

	if (!buttonTexture.loadFromFile(textureFileName))
	{
		GameLogging::LogError("Failed to load in paddle texture");
	}
	else
	{
		buttonShape.setTexture(&buttonTexture);

 	}
}


UIButton::~UIButton()
{
}

void UIButton::Render(sf::RenderWindow * renderWindow)
{
	renderWindow->draw(buttonShape);
}

bool UIButton::hasButtonBeenPressed(sf::Vector2f mousePos)
{
	// Check if button overlaps with the mouse
	sf::Vector2f butPos = buttonShape.getPosition();
	if (butPos.x < mousePos.x   &&
		butPos.x + buttonShape.getTextureRect().width / 2 > mousePos.x &&
		butPos.y < mousePos.y   &&
		buttonShape.getTextureRect().height / 2 + butPos.y > mousePos.y)
	{
		return true;

	}
	return false;
}

 