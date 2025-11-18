#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Bullet.h"
#include "Sound.h"

class Enemy :
    public Entity
{
private:
    bool ishavepistol;
    bool ishaverifle;

    bool isinroom;
    Sound soundpistolreload = Sound("Sounds/Reload-Pistol.wav", false, 100);
    Sound soundpistolshot = Sound("Sounds/Shooting-Pistol.wav", false, 100);

    void inittexture();
    void initsprite();
    void initbools();
    void initmagazine();
    void initframerate();

public:
    Enemy();
    virtual ~Enemy();

    unsigned int framerate;

    sf::Vector2i start;
    sf::Vector2i dest;
    sf::Vector2i Checkpoint[8] = { sf::Vector2i(9,7), sf::Vector2i(26,7), sf::Vector2i(9,26), sf::Vector2i(26,26) , sf::Vector2i(10,8) , sf::Vector2i(27,8) ,sf::Vector2i(10,25) , sf::Vector2i(27,25)};

    unsigned int min;
    unsigned int index;
    unsigned int indexstart;
    unsigned int indexdest;
    unsigned int lastdirection;
    unsigned int functioncount;

    float dt;

    int gapx;
    int gapy;

    bool isfix;
    bool iswalk;

    bool isfinish;
    bool isvanish;

    bool isalert;
    bool ismovegap;
    bool startalert;
    bool startmin;
    bool startcap;
    bool startdistance;
    bool turnpoint;
    bool isstop;
    bool blockshot;

    std::vector<Bullet*> magazine;
    bool isshot;
    bool isstart;
    bool isdisappear;
    bool isplayershot;

    unsigned int shoottimer;
    unsigned int reloadtimer;
    unsigned int shootgap;
    unsigned int gaptimer;

    void checkinroom(float positiongrid_x, float positiongrid_y);
    void checkshot();
    void checkhealth();

    void checkmove(const float& dt);
    void inittrack(float start_x, float start_y, float dest_x, float dest_y);
    void initrandom();
    void tracking();

    void shooting(const float& dt);

    void update(const float& dt);
    void updateentitypos();
    void updatespritepos();
    void render(sf::RenderTarget* target = nullptr);
};

#endif
