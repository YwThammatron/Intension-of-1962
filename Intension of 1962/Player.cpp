#include "Player.h"

void Player::inittexture()
{
	if (!this->texture.loadFromFile("Sprite/SpriteSheet_Agent.png")) {
		std::cout << "Player Spritesheet loading error" << std::endl;
	}
}

void Player::initsprite()
{
	this->sprite.setTexture(this->texture);

	this->spritewidth = this->texture.getSize().x / 6;
	this->spriteheight = this->texture.getSize().y / 4;

	this->sprite.setTextureRect(sf::IntRect(0, 0, this->spritewidth, this->spriteheight));
	this->sprite.setOrigin(this->spritewidth / 2, this->spriteheight);
}

void Player::initbools()
{
	this->ishavepistol = true;
	this->ishavekey = false;
	this->ishaverifle = false;
	this->ishaveaid = false;
	this->ishavemic = false ;

	this->stealthmode = false;
	this->shootmode = false;
	this->walkmode = false;

	this->isshot = false;
	this->isstart = false;
	this->isvanish = false;

	this->shoottimer = 0;
	this->reloadtimer = 0;
	this->shootgap = 0;
}

Player::Player()
{
	this->inittexture();
	this->initsprite();

	this->shape.setSize(sf::Vector2f(10, 115));
	this->shape.setFillColor(sf::Color::Transparent);

	this->healthpoint = 100;
	this->movementspeed = 60;
	this->velocity = 5;

	this->framecount = 0;
	this->animationframe = 1;
	this->enemykilled = 0;

	this->initbools();
}

Player::~Player()
{

}

void Player::checkinroom(float positiongrid_x, float positiongrid_y)
{

}

void Player::checkshot()
{
}

void Player::checkhealth()
{
}

void Player::checkequipment()
{
}

void Player::stealth()
{
}

void Player::move(const float& dt, const float dir_x, const float dir_y)
{
	this->sprite.move(dt * this->movementspeed * dir_x, dt * this->movementspeed * dir_y);
}

void Player::update(const float& dt)
{
	this->updatespritepos();
	this->updateentitypos();
}

void Player::updateentitypos()
{
	this->position = sf::Vector2i(this->sprite.getPosition());
	this->positiongrid = sf::Vector2i(this->position.x / 70, this->position.y / 70);
}

void Player::updatespritepos()
{
	this->shape.setPosition(this->sprite.getPosition().x - 5,this->sprite.getPosition().y - 115);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->shape);
}
