#pragma once
#include "SFML\Graphics.hpp"
#include <string>

/*
UI button object used to creat buttons within game
*/
class UIButton
{
public:
	UIButton();
	/*
	overloaded contructor 

	@param buttonSize
	@param location
	@param textureFileName
	@param window				sfml window being used
	*/
	UIButton(sf::Vector2f buttonSize, sf::Vector2f location, const char* textureFileName, sf::Window* window);
	~UIButton();

	
	/*
	Render button
	*/
	void Render(sf::RenderWindow* renderWindow);

	/*
	Will return if button was pressed
	*/
	bool HasButtonBeenPressed(sf::Vector2i mousePos);

 
protected:
	 
	/*
	sfml render window being used 
	*/
	sf::Window* window;
	/*
	button shape
	*/
	sf::RectangleShape buttonShape;;

	/*
	button texture
	*/
	sf::Texture buttonTexture;

};
