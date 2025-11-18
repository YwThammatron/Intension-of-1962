#ifndef ENTITY_H
#define ENTITY_H

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack> 

class Entity
{
private:

protected:
	sf::Texture texture;

	virtual void inittexture();
	virtual void initsprite();


public:
	Entity();
	virtual ~Entity();

	sf::RectangleShape shape;
	sf::Sprite sprite;

	unsigned int spritewidth;
	unsigned int spriteheight;
	float movementspeed;

	unsigned int framecount;
	unsigned int animationframe;
	unsigned int direction;
	int velocity;

	sf::Vector2i position;
	sf::Vector2i positiongrid;

	sf::Vector2i startpos;
	float distance;
	
	int healthpoint;

	//functions
	virtual void checkinroom(float positiongrid_x,float positiongrid_y);
	virtual void checkshot();
	virtual void checkhealth();

	virtual void move(const float &dt,const float dir_x, const float dir_y);
	virtual void update(const float& dt);
	virtual void updateentitypos();
	virtual void updatespritepos();
	virtual void render(sf::RenderTarget* target = nullptr);
};

#endif

