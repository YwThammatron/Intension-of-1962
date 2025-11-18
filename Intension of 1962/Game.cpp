#include "Game.h"
#include "MainMenuState.h"

//Static functions

//Initializer functions
void Game::initWindow()
{
    //Open window configuration files
    std::ifstream ifs("Config/window.ini");

    //window variables
    std::string title = "None";
    sf::VideoMode window_bounds(1920, 1080);
    unsigned framerate_limit = 60;
    bool Vertical_Sync_Enabled = false;

    //Set files to variables
    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> Vertical_Sync_Enabled;
    }

    ifs.close();

    //Create window at first
	this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(Vertical_Sync_Enabled);
    
}

void Game::initkeys()
{
    //Set supportedkeys 
    this->supportedkeys["Escape"] = sf::Keyboard::Key::Escape;
    this->supportedkeys["A"] = sf::Keyboard::Key::A;
    this->supportedkeys["D"] = sf::Keyboard::Key::D;
    this->supportedkeys["W"] = sf::Keyboard::Key::W;
    this->supportedkeys["S"] = sf::Keyboard::Key::S;
}

void Game::initstates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedkeys, &this->states));
    //this->states.push(new GameState(this->window, &this->supportedkeys));
}


//Constructor/Destructor
Game::Game()
{
    this->initWindow();
    this->initkeys();
    this->initstates();
    
}

Game::~Game()
{
	delete this->window;

    //Clear all states
    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

//functions
void Game::endapplication()
{
    std::cout << "Application end" << std::endl;
}

void Game::updatedt()
{
    //Update dtClock for time to render in 1 frame
    sf::Time timer = this->dtClock.getElapsedTime();
    this->dt = timer.asSeconds();

    this->dtClock.restart().asSeconds();
}


void Game::updateSFMLEvent()
{
    //Update Events
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }

}

void Game::update()
{
    this->updateSFMLEvent();

    //Update top state
    if (!this->states.empty()) {
        this->states.top()->update(this->dt);

        //Delete state and quit if Esc key is pressed
        if (this->states.top()->getquit()) {
            while (!this->states.empty()) {
                this->states.top()->endstate();
                delete this->states.top();
                this->states.pop();
            }
        }
    }
    //Application End
    else {
        this->endapplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();
   
    //Render items

    //Render top state
    if (!this->states.empty()) {
        this->states.top()->render();
    }

    this->window->display();
}

void Game::run()
{
    //Main function
    while (this->window->isOpen())
    {
        this->updatedt();
        this->update();
        this->render();
    }
}


