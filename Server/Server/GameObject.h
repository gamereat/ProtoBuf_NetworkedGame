#pragma once
#include "SFML\Graphics.hpp"

/*
Game object class that all objects inherit from
*/
 class GameObject 
{
public:
	GameObject();
	~GameObject();

	/*
	Get the current postion of the player

	@return the current position of the Game object
	*/
	sf::Vector2f  getPosition();

	/*
	Set the position of game object
	*/
	void setPosition(sf::Vector2f posistion);


	/*
	Gets the sprite used for the gameobject

	@return the sprite for the game object
	*/
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

