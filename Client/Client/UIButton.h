#pragma once
#include "SFML\Graphics.hpp"
#include <string>
class UIButton
{
public:
	UIButton();
	UIButton(sf::Vector2f buttonSize, sf::Vector2f location, const char* textureFileName);
	~UIButton();

	
	void Render(sf::RenderWindow* renderWindow);

	/*
	Will return if button was pressed
	*/
	bool hasButtonBeenPressed(sf::Vector2f mousePos);

 
protected:
	 

	sf::RectangleShape buttonShape;;

	sf::Texture buttonTexture;

};
