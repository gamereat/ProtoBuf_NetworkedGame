#include "GameObject.h"



GameObject::GameObject()
{
	position = sf::Vector2f(0, 0);
}


GameObject::~GameObject()
{
}

sf::Vector2<float> GameObject::getPosition()
{
	return position;
}
