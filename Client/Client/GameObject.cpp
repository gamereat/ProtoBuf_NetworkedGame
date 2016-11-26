#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

sf::Vector2f GameObject::getPosition()
{
	return sprite.getPosition();
}

void GameObject::setPosition(sf::Vector2f position)
{
 	sprite.setPosition(position);
}

void GameObject::setSprite(sf::Sprite sprite)
{
	this->sprite = sprite;
}

void GameObject::SetTexture(sf::Texture texture)
{
	sprite.setTexture(texture);
}
