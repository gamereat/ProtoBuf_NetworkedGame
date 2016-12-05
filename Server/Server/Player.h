#pragma once
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "GameObject.h"

// number of prevous pos to keep on record at any given point 
const int PREVOUS_POS_TO_RECORD = 4;


struct playerInfo
{
	int messageNumber;
	sf::Vector2f pos;
	sf::Vector2f velocity;
	int timeOfUpdat;
	float acceleration;

};

 class Player : public GameObject
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
	 std::vector<playerInfo> messageData;


	sf::Vector2f	perdictedPos;
	void CacaulatePerdictedPos();
	

	sf::Texture paddleTexture;

	int currentScore;

	int playerNumber;

	int estimateLag;


	int gameTimeAtLastUpdate;

};

