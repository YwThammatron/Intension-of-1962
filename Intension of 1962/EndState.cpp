#include "EndState.h"

void EndState::initfonts()
{
	if (!this->font.loadFromFile("Fonts/Title.ttf")) {
		std::cout << "EndState font loading error" << std::endl;
	}
}

void EndState::initkeybinds()
{
	//Set keybinds
	this->keybinds["PAUSE"] = this->supportedkeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedkeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedkeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedkeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedkeys->at("S");
}

void EndState::initbackground()
{
	this->screen = sf::Vector2f(1920.f, 1080.f);

	this->background.setSize(sf::Vector2f(this->screen));
	this->background.setFillColor(sf::Color::Black);
}

void EndState::initbuttons()
{
	//Setup MainMenustate button

	this->buttons["MAINMENU_STATE"] = new Button(500, 900,
		220, 70, &this->font, "Main menu",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["STATISTICS_STATE"] = new Button(1200, 900, 220, 70, &this->font, "Statistics",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

EndState::EndState(sf::RenderWindow* window, std::map<std::string, int>* supportedkeys, std::stack<State*>* states, bool isgoodending, bool isbadending, bool isgameover, int score )
	:State(window, supportedkeys, states)
{
	this->isgoodending = isgoodending;
	this->isbadending = isbadending;
	this->isgameover = isgameover;

	this->initbackground();
	this->initfonts();
	this->initkeybinds();
	this->initbuttons();

	this->currentscore = score;
	this->isplay = false;
}

EndState::~EndState()
{
	for (auto it : buttons) {
		delete it.second;
		std::cout << "Button " << it.first << " deleted\n";
	}
}

void EndState::endstate()
{
	this->soundgoodend.sound.stop();
	this->soundbadend.sound.stop();
	this->soundgameover.sound.stop();
}

void EndState::update(const float& dt)
{
	this->updateMouseposition();
	this->updateinput(dt);
	this->updatebuttons();

	this->textscore.updatestring("Experiences : " + std::to_string(this->currentscore));

	if (this->isgoodending) {
		this->goodending();
	}

	if (this->isbadending) {
		this->badending();
	}

	if (this->isgameover) {
		this->gameover();
	}

}

void EndState::updateinput(const float& dt)
{

}

void EndState::updatebuttons()
{
	//Update all buttons
	for (auto it: buttons) {
		it.second->update(this->mousePosView);
	}

	//main menu button go back to mainmenustate
	if (this->buttons["MAINMENU_STATE"]->isPressed())
	{
		//delete both Endstate and Gamestate
		this->endstate();
		this->states->pop();
	}

	//Check if button statistic is pressed
	if (this->buttons["STATISTICS_STATE"]->isPressed())
	{
		this->endstate();
		this->states->push(new StatState(this->window, this->supportedkeys, this->states));
	}
	
}

void EndState::goodending()
{
	this->textending.updatestring("Victory Ending");
	this->imagesymbol.updatetexture("Endings/Greater_coat_of_arms_of_the_United_States.png",0.2, this->window->getSize().x / 2 - 500, this->window->getSize().y / 2 - 40);
	if (!this->isplay) {

		this->soundgoodend.sound.play();

		std::stringstream dialogue;
		dialogue << "\"The mission has been successfully accomplished.The Soviet Intelligence " << std::endl
			<< "threat was identified by our organization. Through your exceptional courage, " << std::endl
			<< "the impending catastrophic missile conflict was averted. Our foundation " << std::endl
			<< "expresses profound gratitude for your valiant service, particularly in the " << std::endl
			<< "face of significant peril during this mission and throughout your distinguished " << std::endl
			<< "career. In recognition of your exceptional contributions, you were bestowed " << std::endl
			<< "with the prestigious CIA's highest honor upon the completion of your final " << std::endl
			<< "assignment.\" " << std::endl << std::endl
			<< "Your ongoing well - being has been vigilantly ensured by the government.";

		this->textdialogue.updatestring(dialogue.str());
		this->isplay = true;
	}

}

void EndState::badending()
{
	this->textending.updatestring("Cruelty Ending");
	this->textending.text.setFillColor(sf::Color::White);
	this->imagesymbol.updatetexture("Endings/Soviet_coat_of_arms.png",1, this->window->getSize().x / 2 - 500, this->window->getSize().y / 2 - 70);
	
	if (!this->isplay) {
		std::cout << "Bad ending music playing" << std::endl;
		this->soundbadend.sound.play();

		std::stringstream dialogue;
		dialogue << "\"Due to an unforeseen accident that was not of your intention, the " << std::endl
			<< "retrieval of the microfilm from the Soviet headquarters was unsuccessful. " << std::endl
			<< "The Agency finally considered your service in this mission not the foundation " << std::endl
			<< "betrayal but the accidental action due to your strong patriotism for your " << std::endl
			<< "nation. However, this unforeseen circumstance led the Agency to confront an " << std::endl
			<< "unavoidable and perilous missile conflict, posing the most significant " << std::endl
			<< "challenge the CIA has ever encountered.\"" << std::endl << std::endl
			<< "The tensions between the two ideologies have remained unchanged since.";

		this->textdialogue.updatestring(dialogue.str());
		
		this->isplay = true;
	}
}

void EndState::gameover()
{
	this->textending.updatestring("Honory Ending");
	this->imagesymbol.updatetexture("Endings/American_Coat_Of_Arms_Medal.png",0.2, this->window->getSize().x / 2 - 500, this->window->getSize().y / 2 - 30);
	if (!this->isplay) {
		this->soundgameover.sound.play();

		std::stringstream dialogue;
		dialogue << "\"Throughout decades of dedicated service to the foundation," << std::endl
			<< "your unwavering patriotism and steadfast commitment to both nation " << std::endl
			<< "and organization have been unparalleled. The CIA acknowledges the " << std::endl
			<< "sacrifice of their esteemed agent, a stalwart contributor to their " << std::endl
			<< "cause. The foundation bears the responsibility for covering all " << std::endl
			<< "associated costs and adequately compensating your loved ones for the " << std::endl
			<< "sacrifices they endure. In recognition of your exceptional service," << std::endl
			<< "the prestigious medal awarded to agents for courageous actions stands " << std::endl
			<< "as the last crowning achievement in your illustrious career.\" " << std::endl << std::endl
			<< "Your service and dedication to the country will be memorized forever.";

		this->textdialogue.updatestring(dialogue.str());

		this->isplay = true;
	}
}

void EndState::renderbuttons(sf::RenderTarget* target)
{
	for (auto it : buttons) {
		it.second->render(target);
	}
}

void EndState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	this->textending.render(target);
	this->textdialogue.render(target);
	this->imagesymbol.render(target);
	this->textscore.render(target);
	this->renderbuttons(target);
}


