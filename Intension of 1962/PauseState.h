#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "Button.h"
#include "GameState.h"
#include "Text.h"

class PauseState :
    public State
{
private:
    //Variables
    sf::RectangleShape background;
    sf::RectangleShape mainwindow;
    sf::Font font;

    Text textkeys = Text("Fonts/EvilEmpire-4BBVK.ttf", " ", sf::Color::White, 48, 485, 100);
    Text texttips = Text("Fonts/Typewriter.ttf", " ", sf::Color::White, 25, 530, 650);

    std::map<std::string, Button*> buttons;

    bool isplay;

    //functions
    void initfonts();
    void initkeybinds();
    void initbuttons();

public:
    PauseState(sf::RenderWindow* window, std::map <std::string, int>* supportedkeys, std::stack<State*>* states);
    virtual ~PauseState();

    //functions
    void endstate();

    void updateinput(const float& dt);
    void updatebuttons();
    void update(const float& dt);
    void renderbuttons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif
