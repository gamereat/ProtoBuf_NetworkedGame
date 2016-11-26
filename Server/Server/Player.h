#pragma once
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player();
	Player(int score, ServerMessage::Playerinfromation::PlayerType playerType, sf::Vector2f pos);
	~Player();

	void setScore(int newScore);
	int getScore();


	
	void setPlayerType(ServerMessage::Playerinfromation::PlayerType mewType);
	ServerMessage::Playerinfromation::PlayerType getPlayerType();

private:

	ServerMessage::Playerinfromation::PlayerType playerType;

	int currentScore;


};

