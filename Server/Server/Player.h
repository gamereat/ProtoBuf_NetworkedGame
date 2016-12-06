#pragma once
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "PridictedGameObject.h"

/*
Default player class
 inherists from predicted object so is networked 
*/
 class Player : public PridictedGameObject
{
public:
	Player();
	Player(int score, sf::Vector2f pos);
	~Player();

	virtual void Render(sf::RenderWindow* renderWindow);
	virtual void Init();
	virtual void Update(float deltaTime);

	void setScore(int newScore);
	int getScore();


	void UpdatePlayer(ClientMessage::Playerinfromation*,int messageNumber);

 private:

	  

	sf::Texture paddleTexture;

	int currentScore;

	int playerNumber;
  

};

