#pragma once
#include "SFML\Graphics.hpp"
class Menu
{
public:
	Menu();
	~Menu();

	bool Init();

	bool Update();

	bool Render();

private:

	sf::Font MenuFont;

  
};

