#pragma once
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player();
	Player(int score, sf::Vector2f pos);
	~Player();

	void setScore(int newScore);
	int getScore();


	void UpdatePlayer(ClientMessage::Playerinfromation*);
private:

	

	int currentScore;

	int playerNumber;

};

