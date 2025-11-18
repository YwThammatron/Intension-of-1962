#include "CutsceneState.h"

void CutsceneState::initfonts()
{
	if (!this->font.loadFromFile("Fonts/Title.ttf")) {
		std::cout << "EndState font loading error" << std::endl;
	}
}

void CutsceneState::initkeybinds()
{
	//Set keybinds
	this->keybinds["PAUSE"] = this->supportedkeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedkeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedkeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedkeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedkeys->at("S");
}

void CutsceneState::initbackground()
{
	this->screen = sf::Vector2f(1920.f, 1080.f);

	this->background.setSize(sf::Vector2f(this->screen));
	this->background.setFillColor(sf::Color::Black);
}

void CutsceneState::initbuttons()
{
	//Setup MainMenustate button

	this->buttons["GAME_STATE"] = new Button(1475, 900,
		220, 70, &this->font, "Start Mission",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));


}

CutsceneState::CutsceneState(sf::RenderWindow* window, std::map<std::string, int>* supportedkeys, std::stack<State*>* states)
	:State(window, supportedkeys, states)
{

	this->initbackground();
	this->initfonts();
	this->initkeybinds();
	this->initbuttons();

	this->isplay = false;

}

CutsceneState::~CutsceneState()
{
	for (auto it : buttons) {
		delete it.second;
		std::cout << "Button " << it.first << " deleted\n";
	}
}

void CutsceneState::endstate()
{
	this->soundcutscene.sound.stop();
}

void CutsceneState::update(const float& dt)
{
	this->updateMouseposition();
	this->updateinput(dt);
	this->updatebuttons();
	this->updatecutscene();
}

void CutsceneState::updateinput(const float& dt)
{

}

void CutsceneState::updatebuttons()
{
	//Update all buttons
	for (auto it : buttons) {
		it.second->update(this->mousePosView);
	}

	//main menu button go back to mainmenustate
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		//delete both Endstate and Gamestate
		this->endstate();
		this->states->pop();
		this->states->push(new GameState(GameState(this->window, this->supportedkeys, this->states)));
	}

}

void CutsceneState::updatecutscene()
{
	if (!this->isplay) {

		this->soundcutscene.sound.play();

		std::stringstream dialogue;
		dialogue << "In 1962, the intense conflict between two powerful ideologies reached its peak. The Great Patriotic War " << std::endl
			<< "deepened the gap between democracy and socialism, causing a serious divide. Among the socialist " << std::endl
			<< "nations, Cuba, positioned close to the United States, emerged as a significant threat, worsening the " << std::endl
			<< "strain between the two nations." << std::endl << std::endl

			<< "The critical moment occurred in October 1962 with the discovery of the Anadyr operations. The Soviet " << std::endl
			<< "Union, a dominant force in the communist regime, secretly arranged the delivery of ballistic missiles, " << std::endl
			<< "bombers, and infantry to Cuba. This collaboration, led by Fidel Castro and Nikita Khrushchev, aimed to " << std::endl
			<< "weaken the capitalist superpower. The ballistic missiles in Cuba could reach major American cities within " << std::endl
			<< "five minutes, posing a severe threat." << std::endl << std::endl

			<< "Upon learning of the Soviet operation, the United States aimed to counter Soviet support. The U.S. Navy " << std::endl
			<< "sent ships to enforce a blockade, a strategic move to prevent nuclear warfare. However, this action " << std::endl
			<< "increased tensions, casting a dark shadow over the U.S., the Soviet Union, and the entire world, edging " << std::endl
			<< "closer to a potential disaster." << std::endl << std::endl

			<< "You, an experienced CIA agent, accustomed to risky espionage, are assigned a critical task. Disguised as a " << std::endl
			<< "businessperson facing issues with a USSR passport, you must infiltrate the main headquarters of the " << std::endl
			<< "formidable Soviet intelligence organization, the KGB. Your mission is to locate a microfilm containing " << std::endl
			<< "crucial information about the ballistic missile and Operation Anadyr. This intel is vital for CIA espionage, " << std::endl
			<< "offering a potential resolution to the tensions between the two nations. Your duty is to safeguard your " << std::endl
			<< "country from the impending threat." << std::endl << std::endl << std::endl << std::endl 

			<< "The entire world is counting on you." << std::endl;

		this->textdialogue.updatestring(dialogue.str());
		this->isplay = true;
	}

}

void CutsceneState::renderbuttons(sf::RenderTarget* target)
{
	for (auto it : buttons) {
		it.second->render(target);
	}
}

void CutsceneState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	target->draw(this->background);
	this->textdialogue.render(target);
	this->renderbuttons(target);
}



