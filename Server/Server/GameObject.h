#pragma once
#include "SFML\Graphics.hpp"
 class GameObject 
{
public:
	GameObject();
	~GameObject();
	
	sf::Vector2f  getPosition();

	void setPosition(sf::Vector2f);

	sf::Sprite  getSprite();

 protected:
 
	 /*
	 Possition last updated from the clients
	 */
	sf::Vector2f lasteUpdatePosition;
	/*
	Sprite that displays is used to display an object
	*/
	sf::Sprite sprite;
 
	

};

