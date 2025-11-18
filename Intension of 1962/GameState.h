#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseState.h"
#include "EndState.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Text.h"
#include "Sound.h"
#include "Room.h"
#include "Image.h"

class GameState :
    public State
{
    //Game state inherited from State Class
private:
    Map MainFloor;
    Player player;
    sf::Clock clock;

    unsigned int totaltime;

    Text textbullet = Text("Fonts/EvilEmpire-4BBVK.ttf", std::to_string(6 - this->player.shoottimer) + "/" + std::to_string(this->player.bullets), sf::Color::White, 50, this->window->getSize().x/2 + 300, this->window->getSize().y - 200);
    Text texthealth = Text("Fonts/EvilEmpire-4BBVK.ttf", std::to_string(this->player.healthpoint), sf::Color::White, 50, this->window->getSize().x/2 - 350, this->window->getSize().y - 200);
    Text textmiccollect = Text("Fonts/EvilEmpire-4BBVK.ttf", "Microfilm Collected", sf::Color::Transparent, 25, this->window->getSize().x / 2 - 100 , this->window->getSize().y - 200);
    Text textlocation = Text("Fonts/Typewriter.ttf", " ", sf::Color(255, 255, 255) , 30, 70, this->window->getSize().y - 300);
    Image imageheart;

    Sound soundpistolshot = Sound("Sounds/Shooting-Pistol.wav", false, 100);
    Sound soundpistolreload = Sound("Sounds/Reload-Pistol.wav", false, 100);
    Sound soundfirstaid = Sound("Sounds/ItemPickup-FirstAid.wav", false, 75);
    Sound sounditem = Sound("Sounds/ItemPickup-General.wav", false, 100);

    bool ispause;

    sf::View mainview;

    unsigned int framerate;
    unsigned int playercode;
    unsigned int furntile[72];

    unsigned int pathtile1[4] = { 3,4,31,9 };
    unsigned int pathtile2[4] = { 16,5,13,7 };
    unsigned int pathtile3[4] = { 11,12,24,23 };
    unsigned int pathtile4[4] = { 6,14,8,15 };

    Room rooms[9] = {Room(5,9),Room(7,8),Room(3,8),Room(9,4),Room(5,3),Room(8,4),Room(6,3),Room(5,9),Room(13,8)};
    sf::Vector2i roominitpos[9] = { sf::Vector2i(4,5),sf::Vector2i(11,9),sf::Vector2i(6,19),sf::Vector2i(9,27),sf::Vector2i(18,27),sf::Vector2i(37,27),sf::Vector2i(31,27),sf::Vector2i(18,9),sf::Vector2i(31,9) };

    sf::Vector2f spawnpos[10] = { sf::Vector2f(25.5,22),sf::Vector2f(28.5,22),sf::Vector2f(23.5,25),sf::Vector2f(30.5,25),sf::Vector2f(15.5,25),sf::Vector2f(18.5,7),sf::Vector2f(35.5,7),sf::Vector2f(41.5,25),sf::Vector2f(23,5),sf::Vector2f(31,5)};
    sf::Vector2f roompos[8] = { sf::Vector2f(10,26),sf::Vector2f(9,25),sf::Vector2f(21,26),sf::Vector2f(9,8),sf::Vector2f(15,7),sf::Vector2f(38,7),sf::Vector2f(33,26),sf::Vector2f(40,26) };
    sf::Vector2i inroompos[10] = { sf::Vector2i(7, 7), sf::Vector2i(5, 12), sf::Vector2i(12, 30), sf::Vector2i(16, 29), sf::Vector2i(12, 13), sf::Vector2i(16, 12), sf::Vector2i(20, 16), sf::Vector2i(35, 11), sf::Vector2i(36, 15), sf::Vector2i(43, 29) };
    sf::Vector2i Checkpoint[8] = { sf::Vector2i(9,7), sf::Vector2i(26,7), sf::Vector2i(9,26), sf::Vector2i(26,26) , sf::Vector2i(10,8) , sf::Vector2i(27,8) ,sf::Vector2i(10,25) , sf::Vector2i(27,25) };

    std::vector<Enemy*>fixenemy;
    std::vector<Enemy*>walkenemy;
    std::vector<Enemy*>roomenemy;

    unsigned int items[4] = { 170,171,172,173 };
    sf::Vector2i itempos[16] = { sf::Vector2i(5,9),sf::Vector2i(6,11), sf::Vector2i(7,21), sf::Vector2i(10,29),sf::Vector2i(16,28), sf::Vector2i(21,28), sf::Vector2i(32,28), sf::Vector2i(37,31),sf::Vector2i(41,28), sf::Vector2i(13,11),sf::Vector2i(15,12), sf::Vector2i(20,11),sf::Vector2i(19,14), sf::Vector2i(35,11),sf::Vector2i(39,11),sf::Vector2i(38,13) };
    sf::Vector2i micpos[7] = { sf::Vector2i(6,7),sf::Vector2i(21,14),sf::Vector2i(16,10),sf::Vector2i(21,14),sf::Vector2i(14,29),sf::Vector2i(19,28),sf::Vector2i(38,28) };
    unsigned int micindex;
    unsigned int tilecode_x;
    unsigned int tilecode_y;
    unsigned int itemindex;
    unsigned int fadecount;
    unsigned int colorindex;

    unsigned int endcount;
    int score;
    bool iswrite;
    bool isupdatetex;
    bool isfadecolor;

    void initframerate();
    void initkeybinds();
    void initview();
    void initposition();
    void initmagazine();
    void initspawn();
    void initroomspawn();
    void initrooms();
    void inititems();

public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedkeys, std::stack<State*>* states);
    virtual ~GameState();

    //functions
    void endstate();

    void updatedt(const float& dt);

    void updateinput(const float& dt);
    void updateposition();
    void updateview();
    void updaterooms();
    void updatetime();
    void updateitems();

    void checkforpause();

    void shootmode();

    void collision();
    void equipments();
    void shooting(const float& dt);
    void response();

    void healthpoint();

    void endgame();
    void writescore(int score);

    void update(const float &dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif

