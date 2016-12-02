#include "GameObject.h"



GameObject::GameObject()
{
 
}


GameObject::~GameObject()
{
}

sf::Vector2f GameObject::getPosition()
{

	this->position = sprite.getPosition();;

	return sprite.getPosition();
}

void GameObject::setPosition(sf::Vector2f position)
{
	this->position = position;

	sprite.setPosition(position);
	
	
}

sf::Sprite GameObject::getSprite()
{
	return sprite;
}
