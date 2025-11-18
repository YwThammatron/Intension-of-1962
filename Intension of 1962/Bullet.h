#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet
{
private:
	sf::Texture texture;
	

	void inittexture();
	void initsprite();

public:
	sf::Sprite sprite;

	unsigned int direction;
	unsigned int movementspeed;
	int velocity;

	unsigned int spritewidth;
	unsigned int spriteheight;

	Bullet();
	virtual ~Bullet();

	void update(const float& dt);
	void move(const float& dt, const float dir_x, const float dir_y);

	void render(sf::RenderTarget* target = nullptr);
};

#endif

