#include "Bullet.h"

void Bullet::inittexture()
{
	if (!this->texture.loadFromFile("Bullet/SpriteSheet_Bullet.png")) {
		std::cout << "Bullet texture loading error" << std::endl;
	}
}

void Bullet::initsprite()
{
	this->sprite.setTexture(this->texture);

	this->spritewidth = this->texture.getSize().x / 4;
	this->spriteheight = this->texture.getSize().y;

	this->sprite.setTextureRect(sf::IntRect(0, 0, this->spritewidth, this->spriteheight));
	this->sprite.setOrigin(this->spritewidth / 2, this->spriteheight / 2);
}

Bullet::Bullet()
{
	this->inittexture();
	this->initsprite();

	this->direction = 0;
	this->movementspeed = 60;
	this->velocity = 10;
}

Bullet::~Bullet()
{
}

void Bullet::update(const float& dt)
{

}

void Bullet::move(const float& dt, const float dir_x, const float dir_y)
{
	this->sprite.move(dt * this->movementspeed * dir_x, dt * this->movementspeed * dir_y);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
