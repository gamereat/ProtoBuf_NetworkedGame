#include "Menu.h"
#include "GameLogging.h"
#include "ClientController.h"

Menu::Menu()
{
}


Menu::~Menu()
{
}

bool Menu::Init(sf::Window* renderWindo)
{

	// init the fonts 
	if (!MenuFont.loadFromFile("../res/font/Politik.otf"))
	{
		GameLogging::LogError("Standard font faile to load");
		return false;
	}

	MainText.setFont(MenuFont);

	playButton = new UIButton(sf::Vector2f(118,58), sf::Vector2f(SCREEN_SIZE.x / 2 - 59,250), "../res/art/play-button.png", renderWindo);

	exitButton = new UIButton(sf::Vector2f(118, 58), sf::Vector2f(SCREEN_SIZE.x / 2 - 59, 325), "../res/art/exit-button.png", renderWindo);


	optionsButtons = new UIButton(sf::Vector2f(118, 58), sf::Vector2f(SCREEN_SIZE.x / 2 - 59,400), "../res/art/options-button.png", renderWindo);

	

	
	return true;
}

bool Menu::Update()
{
	if (playButton->HasButtonBeenPressed(sf::Mouse::getPosition()))
	{
		return true;

	}
	if (exitButton->HasButtonBeenPressed(sf::Mouse::getPosition()))
	{
 
	}	
	if (optionsButtons->HasButtonBeenPressed(sf::Mouse::getPosition()))
	{
 	}

	return false;
}

bool Menu::Render(sf::RenderWindow* renderWindow)
{
	playButton->Render(renderWindow);
	exitButton->Render(renderWindow);
	optionsButtons->Render(renderWindow);

	return true;
}
