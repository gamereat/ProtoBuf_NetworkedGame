#include "GameObject.h"



GameObject::GameObject()
{
 }


GameObject::~GameObject()
{
}

sf::Vector2f GameObject::getPosition()
{
	return position;
}

void GameObject::setPosition(sf::Vector2f position)
{
	this->position = position;
}
