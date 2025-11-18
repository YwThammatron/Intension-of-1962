#ifndef ROOM_H
#define ROOM_H

#include "Entity.h"

class Room
{
private:
	unsigned int roomwidth;
	unsigned int roomheight;

	void initshape();
	
public:
	Room(unsigned int width,unsigned int height);
	virtual ~Room();

	sf::RectangleShape room;

	void initposition(unsigned int room_x,unsigned int room_y);
	void inroom();
	void outroom();

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

#endif

