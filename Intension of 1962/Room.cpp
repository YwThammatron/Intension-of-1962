#include "Room.h"

void Room::initshape()
{
	this->room.setSize(sf::Vector2f(this->roomwidth * 70, this->roomheight * 70));
	this->room.setFillColor(sf::Color(67, 66, 66));
}

Room::Room(unsigned int width, unsigned int height)
{
	this->roomwidth = width;
	this->roomheight = height;

	this->initshape();
}

Room::~Room()
{

}

void Room::initposition(unsigned int room_x, unsigned int room_y)
{
	this->room.setPosition(room_x * 70, room_y * 70);
}

void Room::inroom()
{
	this->room.setFillColor(sf::Color::Transparent);
}

void Room::outroom()
{
	this->room.setFillColor(sf::Color(67,66,66));
}

void Room::update(const float& dt)
{

}

void Room::render(sf::RenderTarget* target)
{
	target->draw(this->room);
}
