#include "PauseState.h"

void PauseState::initfonts()
{
	if (!this->font.loadFromFile("Fonts/Title.ttf")) {
		std::cout << "PauseState:font loading error" << std::endl;
	}
}

void PauseState::initkeybinds()
{
	//Sey keybinds
	this->keybinds["PAUSE"] = this->supportedkeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedkeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedkeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedkeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedkeys->at("S");

}

void PauseState::initbuttons()
{
	this->buttons["GAME_STATE"] = new Button(this->mainwindow.getPosition().x + 100, this->mainwindow.getPosition().y + 600, 
		200, 70, &this->font, "Continue",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["MAINMENU_STATE"] = new Button(this->mainwindow.getPosition().x + 450, this->mainwindow.getPosition().y + 600,
		200, 70, &this->font, "Main menu",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(this->mainwindow.getPosition().x + 800, this->mainwindow.getPosition().y + 600,
		200, 70, &this->font, "QUIT",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

PauseState::PauseState(sf::RenderWindow* window, std::map <std::string, int>* supportedkeys, std::stack<State*>* states)
	:State(window, supportedkeys, states)
{
	//Set up screen
	this->screen = sf::Vector2f(1920.f, 1080.f);
	
	//Setup Background
	this->background.setSize(this->screen);
	this->background.setFillColor(sf::Color::Transparent);

	this->mainwindow.setSize(sf::Vector2f(1080.f, 720.f));
	this->mainwindow.setFillColor(sf::Color::Black);
	this->mainwindow.setPosition((this->window->getSize().x - 1080) / 2.f, 
		(this->window->getSize().y - 720) / 2.f - 50);

	//Initializer
	this->initfonts();
	this->initkeybinds();
	this->initbuttons();

	this->isplay = false;
	
}

PauseState::~PauseState()
{
	//delete all buttons
	for (auto it : buttons) {
		delete it.second;
		std::cout << "Button " << it.first << " deleted\n";
	}
}

void PauseState::endstate()
{
	std::cout << "Pausestate end" << std::endl;
}

void PauseState::updateinput(const float& dt)
{
	this->checkforquit();
}

void PauseState::updatebuttons()
{
	//Update all buttons
	for (auto it : buttons) {
		it.second->update(this->mousePosView);
	}

	//resume button go back to gamestate
	if (this->buttons["GAME_STATE"]->isPressed()) 
	{
		//delete PauseState
		this->states->pop();
	}

	//main menu button go back to mainmenustate
	if (this->buttons["MAINMENU_STATE"]->isPressed()) 
	{
		//delete both Pausestate and Gamestate
		this->states->pop();
		this->states->pop();
	}

	//Check if button statistic is pressed
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quit = true;
	}
	 
}

void PauseState::update(const float& dt)
{
	this->updateMouseposition();
	this->updateinput(dt);
	this->updatebuttons();

	if (!this->isplay) {
		std::stringstream keys;
		std::stringstream tips;

		keys << "								  Control Keys" << std::endl << std::endl

			<< "	Main Control											WASD" << std::endl
			<< "	Enable Shooting Mode					 			Q" << std::endl
			<< "	Disable Shooting Mode								E" << std::endl
			<< "	Shooting												Left Click" << std::endl
			<< "	Open Pause Menu										Esc" << std::endl << std::endl << std::endl;


		tips << "Tips : Try to located microfilm in the rooms, other items will support you.";

		this->textkeys.updatestring(keys.str());
		this->texttips.updatestring(tips.str());

		this->isplay = true;
	}
}

void PauseState::renderbuttons(sf::RenderTarget* target)
{
	for (auto it : buttons) {
		it.second->render(target);
	}
}

void PauseState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	target->draw(this->mainwindow);
	this->textkeys.render(target);
	this->texttips.render(target);
	this->renderbuttons(target);
}
