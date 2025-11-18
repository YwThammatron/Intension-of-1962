#include "MainMenuState.h"

void MainMenuState::initfonts()
{
	if (!this->normalfont.loadFromFile("Fonts/Default.ttf")) {
		std::cout << "MainMenuState:Font loading error" << std::endl;
	}

	if (!this->titlefont.loadFromFile("Fonts/Title.ttf")) {
		std::cout << "MainMenuState:Font loading error" << std::endl;
	}
}

void MainMenuState::initkeybinds()
{
	//Set keybinds
	this->keybinds["PAUSE"] = this->supportedkeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedkeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedkeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedkeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedkeys->at("S");

}

void MainMenuState::initbuttons()
{
	//Setup MainMenustate button
	this->buttons["CUTSCENE_STATE"] = new Button(100, 245, 220, 70, &this->titlefont, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["STATISTICS_STATE"] = new Button(100, 420, 220, 70, &this->titlefont, "Statistics",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(100, 595, 220, 70, &this->titlefont, "QUIT",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

void MainMenuState::initbackground()
{
	if (!this->texture.loadFromFile("State_Backgrounds/MainMenuState_Background.png")) {
		std::cout << "MainMenuState background texture loading error" << std::endl;
	}

	this->background.setTexture(this->texture);
	this->background.setPosition(0, 0);
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedkeys, std::stack<State*>* states)
	:State(window, supportedkeys,states)
{	
	//Setup screen
	this->screen = sf::Vector2f(1920.f, 1080.f);

	this->initbackground();
	
	//Initializer
	this->initfonts();
	this->initkeybinds();
	this->initbuttons();

}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void MainMenuState::updateinput(const float& dt)
{
	this->checkforquit();

	//Update player input
}

void MainMenuState::updatebuttons()
{
	//Update all buttons in buttons map
	for (auto it : buttons) {
		it.second->update(this->mousePosView);
	}

	//Check if button new game is pressed
	if (this->buttons["CUTSCENE_STATE"]->isPressed())
	{
		this->states->push(new CutsceneState(this->window, this->supportedkeys, this->states));
	}

	//Check if button statistic is pressed
	if (this->buttons["STATISTICS_STATE"]->isPressed()) 
	{
		this->states->push(new StatState(this->window, this->supportedkeys, this->states));
	}

	//Check if button exit is pressed
	if (this->buttons["EXIT_STATE"]->isPressed()) 
	{
		this->quit = true;
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMouseposition();
	this->updateinput(dt);
	this->updatebuttons();

	this->texttitle.updatestring("THE INTENSION OF 1962");
}

void MainMenuState::renderbuttons(sf::RenderTarget* target)
{
	for (auto it : buttons) {
		it.second->render(target);
	}
}

void MainMenuState::endstate()
{
	std::cout << "MainMenuState end" << std::endl;
}

void MainMenuState::render(sf::RenderTarget* target)
{
	//If target binding to nothing then it will bind to window
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	this->texttitle.render(target);
	this->renderbuttons(target);
	this->textpurpose.render(target);
	this->textprofile.render(target);
	
}


