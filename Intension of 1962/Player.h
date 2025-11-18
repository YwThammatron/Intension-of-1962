#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Bullet.h"

class Player :
    public Entity
{
private:

    void inittexture();
    void initsprite();
    void initbools();

    
public:
    Player();
    virtual ~Player();

    unsigned int shoottimer;
    unsigned int reloadtimer;

    bool ishavekey;
    bool ishavepistol;
    bool ishaverifle;
    bool ishaveaid;
    bool ishavemic;

    bool isinroom;
    bool stealthmode;
    bool shootmode;
    bool walkmode;
    unsigned int bullets;
    int shootgap;

    std::vector<Bullet*> magazine;
    bool isshot;
    bool isstart;
    bool isvanish;

    unsigned int enemykilled;

    void checkinroom(float positiongrid_x, float positiongrid_y);
    void checkshot();
    void checkhealth();
    void checkequipment();
    void stealth();

    void move(const float& dt, const float dir_x, const float dir_y);
    void update(const float& dt);
    void updateentitypos();
    void updatespritepos();
    void render(sf::RenderTarget* target = nullptr);
    
};

#endif 

