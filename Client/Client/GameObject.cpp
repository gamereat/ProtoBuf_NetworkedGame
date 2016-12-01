#include "GameObject.h"
#include "GameLogging.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}


void GameObject::setSprite(sf::Sprite sprite)
{
	this->sprite = sprite;
}

void GameObject::SetTexture(sf::Texture texture)
{
	sprite.setTexture(texture);
}
