#pragma once
#include "SFML\Graphics.hpp"

class GameObject 
{
public:
	GameObject();
	~GameObject();

	sf::Vector2f  getPosition();

protected:
 

	/*
	Sprite that displays is used to display an object
	*/
	sf::Sprite sprite;

	/*
	Holds the position of the object
	*/
	sf::Vector2f position;
	

};

