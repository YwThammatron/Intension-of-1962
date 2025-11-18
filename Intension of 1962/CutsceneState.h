#ifndef CUTSCENESTATE_H
#define CUTSCENESTATE_H

#include "State.h"
#include "GameState.h"
#include "Text.h"
#include "Sound.h"
#include "Button.h"
class CutsceneState :
    public State
{
private:
    sf::RectangleShape background;
    sf::Font font;

    Text textdialogue = Text("Fonts/Typewriter.ttf", " ", sf::Color::White, 30, this->window->getSize().x / 2 - 750, this->window->getSize().y / 2 - 450);
    Sound soundcutscene = Sound("Sounds/LobbyTenseSound.wav", true, 100);

    std::map<std::string, Button*> buttons;
    bool isplay;

    void initfonts();
    void initkeybinds();
    void initbackground();
    void initbuttons();

public:
    CutsceneState(sf::RenderWindow* window, std::map<std::string, int>* supportedkeys, std::stack<State*>* states);
    virtual ~CutsceneState();

    void endstate();

    void update(const float& dt);
    void updateinput(const float& dt);
    void updatebuttons();
    void updatecutscene();

    void render(sf::RenderTarget* target = nullptr);
    void renderbuttons(sf::RenderTarget* target = nullptr);
};

#endif

