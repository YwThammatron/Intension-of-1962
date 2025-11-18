#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "StatState.h"
#include "Text.h"
#include "Image.h"
#include "Sound.h"
#include "Button.h"

class EndState :
    public State
{
private:
    sf::RectangleShape background;
    sf::Font font;

    Text textending = Text("Fonts/Title.ttf", " ", sf::Color::White, 70, this->window->getSize().x / 2 - 210, 100);
    Text textscore = Text("Fonts/Typewriter.ttf", " ", sf::Color::White, 50, this->window->getSize().x / 2 - 205, this->window->getSize().y/2 + 260);
    Text textdialogue = Text("Fonts/Typewriter.ttf", " ", sf::Color::White, 30, this->window->getSize().x / 2 - 205, this->window->getSize().y / 2 - 200);
    Image imagesymbol;

    Sound soundgoodend = Sound("Sounds/US March_The Army Goes Rolling Along (Instrumental)-HQ.wav", false, 40);
    Sound soundbadend = Sound("Sounds/The Sacred War (Instrumental)-HQ.wav", false, 60);
    Sound soundgameover = Sound("Sounds/Taps-HQ.wav" ,false, 100);

    std::map<std::string, Button*> buttons;
    int currentscore;
    bool isplay;

    void initfonts();
    void initkeybinds();
    void initbackground();
    void initbuttons();

public:
    EndState(sf::RenderWindow* window, std::map<std::string, int>* supportedkeys, std::stack<State*>* states, bool isgoodending, bool isbadending, bool isgameover, int score);
    virtual ~EndState();

    void endstate();

    void update(const float& dt);
    void updateinput(const float& dt);
    void updatebuttons();

    void goodending();
    void badending();
    void gameover();
    void render(sf::RenderTarget* target = nullptr);
    void renderbuttons(sf::RenderTarget* target = nullptr);
};

#endif

