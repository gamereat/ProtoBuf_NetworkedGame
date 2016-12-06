#include "GameObject.h"



GameObject::GameObject()
{
	
	lasteUpdatePosition = sf::Vector2f(0,0);
}


GameObject::~GameObject()
{
}

sf::Vector2f GameObject::getPosition()
{
	// gets the latest position from the sprite
	this->lasteUpdatePosition = sprite.getPosition();;

	return sprite.getPosition();
}

void GameObject::setPosition(sf::Vector2f position)
{

	this->lasteUpdatePosition = position;

	sprite.setPosition(position);
	
 }

sf::Sprite GameObject::getSprite()
{
	return sprite;
}
