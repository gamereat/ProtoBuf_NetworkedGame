#include "GameObject.h"



GameObject::GameObject()
{
 
}


GameObject::~GameObject()
{
}

sf::Vector2f GameObject::getPosition()
{

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
