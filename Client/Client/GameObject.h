#pragma once
#include "SFML\Graphics.hpp"

class GameObject 
{
public:
	GameObject();
	~GameObject();

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow*) = 0;

	

protected:
	virtual void HandleInput(float deltaTime) = 0;


	/*
	Sprite that displays is used to display an object
	*/
	sf::Sprite sprite;

	/*
	Holds the position of the object
	*/
	sf::Vector3<float> position;
	

};

