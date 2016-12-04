#pragma once
#include "SFML\Graphics.hpp"
#include <string>
class UIButton
{
public:
	UIButton();
	UIButton(sf::Vector2f buttonSize, sf::Vector2f location, const char* textureFileName, sf::Window* window);
	~UIButton();

	
	void Render(sf::RenderWindow* renderWindow);

	/*
	Will return if button was pressed
	*/
	bool HasButtonBeenPressed(sf::Vector2i mousePos);

 
protected:
	 
	sf::Window* window;
	sf::RectangleShape buttonShape;;

	sf::Texture buttonTexture;

};
