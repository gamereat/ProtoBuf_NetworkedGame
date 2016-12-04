#pragma once
#include "SFML\Graphics.hpp"
#include "UIButton.h"
class Menu
{
public:
	Menu();
	~Menu();

	bool Init(sf::Window* renderWindo);

	bool Update();

	bool Render(sf::RenderWindow* renderWindow);

private:

	sf::Font MenuFont;

	sf::Text MainText;

	/*
	UI button which will be used to take player to play state
	*/
	UIButton* playButton;


	/*
	UI button which will exit the application
	*/
	UIButton* exitButton;


	/*
	UI button which will be used to take player to options screen
	*/
	UIButton* optionsButtons;
};

