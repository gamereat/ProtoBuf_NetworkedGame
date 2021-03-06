#pragma once
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "GameObject.h"

// number of prevous pos to keep on record at any given point 
const int PREVOUS_POS_TO_RECORD = 4;

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


	void UpdatePlayer(ClientMessage::Playerinfromation*);

	float clamp(float lower, float upper, float num);
private:

	sf::Vector2f perdictedPos;


	std::vector<sf::Vector2f> prevousPosition;
	
	std::vector<int> prevousMessageTimes;

	std::vector<int> timeOfLastUpdate;

	std::vector<sf::Vector2f> prevousVelocity;
	void CacaulatePerdictedPos();
	

	sf::Texture paddleTexture;

	int currentScore;

	int playerNumber;

	int estimateLag;


	int gameTimeAtLastUpdate;

};

