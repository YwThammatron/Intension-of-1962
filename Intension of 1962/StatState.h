#ifndef STATSTATE_H
#define STATSTATE_H

#include "GameState.h"
#include "Text.h"
#include "button.h"

class StatState :
    public State
{
private:
    //Variables
    sf::Font font;

    int score;
    unsigned int index;
    bool isread;

    std::map<std::string, Button*> buttons;
    std::vector<int> scoreboard;

    Text textscoreboard = Text("Fonts/Typewriter.ttf", "Scoreboard", sf::Color::White, 60, 850, 50 + (150 * 0));

    Text textrank1 = Text("Fonts/Typewriter.ttf", "Previous Experience #1 : -", sf::Color::White, 35, 850, 200 + (125 * 0));
    Text textrank2 = Text("Fonts/Typewriter.ttf", "Previous Experience #2 : -", sf::Color::White, 35, 850, 200 + (125 * 1));
    Text textrank3 = Text("Fonts/Typewriter.ttf", "Previous Experience #3 : -", sf::Color::White, 35, 850, 200 + (125 * 2));
    Text textrank4 = Text("Fonts/Typewriter.ttf", "Previous Experience #4 : -", sf::Color::White, 35, 850, 200 + (125 * 3));
    Text textrank5 = Text("Fonts/Typewriter.ttf", "Previous Experience #5 : -", sf::Color::White, 35, 850, 200 + (125 * 4));
    
    //functions
    void initfonts();
    void initkeybinds();
    void initbuttons();
    void initbackground();

public:
    StatState(sf::RenderWindow* window, std::map<std::string, int>* supportedkeys, std::stack<State*>* states);
    virtual ~StatState();

    //functions
    void endstate();

    void updateinput(const float& dt);
    void updatebuttons();
    void updatescore();
    void inittext();
    void update(const float& dt);
    void renderbuttons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
};

#endif

