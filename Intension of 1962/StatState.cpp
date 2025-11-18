#include "StatState.h"

void StatState::initfonts()
{
	if (!this->font.loadFromFile("Fonts/Title.ttf")) {
		std::cout << "Statstate:font loading error" << std::endl;
	}
}

void StatState::initkeybinds()
{
	//Set keybinds
	this->keybinds["PAUSE"] = this->supportedkeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedkeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedkeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedkeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedkeys->at("S");

}

void StatState::initbuttons()
{
	this->buttons["MAINMENU_STATE"] = new Button(this->background.getPosition().x + 80, this->background.getPosition().y + 900,
		220, 70, &this->font, "<- Back",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

void StatState::initbackground()
{
	if (!this->texture.loadFromFile("State_Backgrounds/StatState_Background.png")) {
		std::cout << "Statstate:Background loading error" << std::endl;
	}

	this->background.setTexture(this->texture);
	this->background.setPosition(0, 0);
}

StatState::StatState(sf::RenderWindow* window, std::map<std::string, int>* supportedkeys, std::stack<State*>* states)
	:State(window,supportedkeys,states)
{
	//Setup Screen
	this->screen = sf::Vector2f(this->window->getSize().x, this->window->getSize().y);

	//Setup background
	this->initbackground();

	//Initializer
	this->initfonts();
	this->initkeybinds();
	this->initbuttons();

	this->isread = false;
	this->index = 0;
}

StatState::~StatState()
{
	//delete all buttons
	for (auto it : buttons) {
		delete it.second;
		std::cout << "Button " << it.first << " deleted" << std::endl;
	}
}

void StatState::endstate()
{
	std::cout << "StatState end" << std::endl;
}

void StatState::updateinput(const float& dt)
{
	this->checkforquit();
}

void StatState::updatebuttons()
{
	for (auto it : buttons) {
		it.second->update(this->mousePosView);
	}

	//Go back to MainMenuState
	if (this->buttons["MAINMENU_STATE"]->isPressed()) {
		this->states->pop();
	}
}

void StatState::updatescore()
{
		std::ifstream file("Config/scoreboard.txt");

		if (file.is_open() && !this->isread) {

			while (file >> this->score) {
				this->scoreboard.push_back(this->score);
				//std::cout << "Size : " << this->scoreboard.size() << std::endl;
				this->index++;
			}

			this->isread = true;
		}

		file.close();

		while (this->scoreboard.size() < 5) {
			this->scoreboard.push_back(0);
			this->index++;
		}

		std::sort(this->scoreboard.begin(), this->scoreboard.end());

		this->textrank1.updatestring("Previous Experience: Order #1 : " + std::to_string(this->scoreboard[this->index - 1]));
		this->textrank2.updatestring("Previous Experience: Order #2 : " + std::to_string(this->scoreboard[this->index - 2]));
		this->textrank3.updatestring("Previous Experience: Order #3 : " + std::to_string(this->scoreboard[this->index - 3]));
		this->textrank4.updatestring("Previous Experience: Order #4 : " + std::to_string(this->scoreboard[this->index - 4]));
		this->textrank5.updatestring("Previous Experience: Order #5 : " + std::to_string(this->scoreboard[this->index - 5]) + "|");
}

void StatState::update(const float& dt)
{
	this->updateMouseposition();
	this->updateinput(dt);
	this->updatebuttons();

	this->updatescore();
}

void StatState::renderbuttons(sf::RenderTarget* target)
{
	for (auto it : buttons) {
		it.second->render(target);
	}
}

void StatState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	this->renderbuttons(target);
	this->textscoreboard.render(target);
	this->textrank1.render(target);
	this->textrank2.render(target);
	this->textrank3.render(target);
	this->textrank4.render(target);
	this->textrank5.render(target);

}
