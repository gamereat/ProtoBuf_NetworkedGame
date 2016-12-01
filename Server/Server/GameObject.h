#pragma once
#include "SFML\Graphics.hpp"
#include "../ShaderControlls/constantHeader.h"
class GameObject 
{
public:
	GameObject();
	~GameObject();
	
	sf::Vector2f  getPosition();

	void setPosition(sf::Vector2f);
 protected:
 
	sf::Vector2f position;
	/*
	Sprite that displays is used to display an object
	*/
	sf::Sprite sprite;
 
	

};

