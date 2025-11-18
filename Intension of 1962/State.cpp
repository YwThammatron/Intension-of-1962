#include "State.h"

State::State(sf::RenderWindow *window, std::map<std::string, int>* supportedkeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedkeys = supportedkeys;
	this->states = states;
	this->quit = false;
	this->isgoodending = false;
	this->isbadending = false;
	this->isgameover = false;
}

State::~State()
{

}

const bool& State::getquit() const
{
	return this->quit;
}



void State::updateMouseposition()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::checkforquit()
{
	//Check if Esc key is pressed
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
		this->quit = true;
	}*/
}
