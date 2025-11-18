#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "StatState.h"
#include "CutsceneState.h"
#include "Text.h"
#include "Button.h"

class MainMenuState :
    public State
{
private:
    //Variables
    sf::Font titlefont;
    sf::Font normalfont;

    Text texttitle = Text("Fonts/Title.ttf", "THE INTENSION OF 1962", sf::Color::White, 110, 75 , 50);
    Text textpurpose = Text("Fonts/Default.ttf", "For Educational Purpose Only. All Rights not Reserved", sf::Color::White, 25, 100, 900);
    Text textprofile = Text("Fonts/Default.ttf", "Designated by Thammatorn Tanasamanchoke 66010358 for kmitl project", sf::Color::White, 25, 100, 900 + 35);

    std::map<std::string, Button*> buttons;

    //functions
    void initfonts();
    void initkeybinds();
    void initbuttons();
    void initbackground();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedkeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    //functions
    void endstate();

    void updateinput(const float& dt);
    void updatebuttons();
    void update(const float& dt);
    void renderbuttons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);

};

#endif

