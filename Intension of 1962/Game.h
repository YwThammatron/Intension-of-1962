#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"
#include "EndState.h"

class Game
{
	//Core Class
private:

	//Variables
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	//State stack
	std::stack <State*> states;

	//Supported Keys map
	std::map<std::string, int> supportedkeys;

	//Initialization
	void initWindow();
	void initstates();
	void initkeys();

public:
	//Constructor/Destructor
	Game();
	virtual ~Game();

	//functions

	//Regular
	void endapplication();

	//Update
	void updatedt();
	void updateSFMLEvent();
	void update();

	//Render
	void render();

	//Main
	void run();
};

#endif
