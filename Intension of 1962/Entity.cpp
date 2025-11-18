#include "Entity.h"

void Entity::inittexture()
{

}

void Entity::initsprite()
{
	
}

Entity::Entity()
{
	this->movementspeed = 60;
	this->direction = 0;
}

Entity::~Entity()
{

}

void Entity::checkinroom(float positiongrid_x, float positiongrid_y)
{

}

void Entity::checkshot()
{
}

void Entity::checkhealth()
{
}


void Entity::move(const float &dt,const float dir_x, const float dir_y)
{
	this->shape.move(dir_x * this->movementspeed * dt, dir_y * this->movementspeed * dt);
}

void Entity::update(const float& dt)
{
	this->updateentitypos();
	this->updatespritepos();
}

void Entity::updateentitypos()
{
	this->position = sf::Vector2i(this->sprite.getPosition().x, this->sprite.getPosition().y);
}

void Entity::updatespritepos()
{
	this->sprite.setPosition(this->shape.getPosition());
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->sprite);
}

