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
 
	sf::Vector2f position;
	/*
	Sprite that displays is used to display an object
	*/
	sf::Sprite sprite;
 
	

};

