#ifndef STATE_H
#define STATE_H

#include "Entity.h"

class State
{
private:
	
	//Base Class for all states
protected:
	//Copy stack of states in game.h
	std::stack<State*>* states;

	sf::RenderWindow* window;
	std::map<std::string, int>* supportedkeys;
	std::map<std::string, int> keybinds;

	sf::Vector2f screen;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	bool quit;
	bool isgoodending;
	bool isbadending;
	bool isgameover;

	//Resources
	sf::Sprite background;
	sf::Texture texture;

	//functions
	virtual void initkeybinds() = 0;

public:
	State(sf::RenderWindow* window,std::map<std::string,int>* supportedkeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getquit() const;

	//functions
	virtual void endstate() = 0;
	virtual void updateMouseposition();
	virtual void updateinput(const float& dt) = 0;
	virtual void checkforquit();
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

#endif
