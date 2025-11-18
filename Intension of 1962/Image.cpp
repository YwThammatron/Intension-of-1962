#include "Image.h"

void Image::inittexture()
{
	if (!this->isloadtexture) {
		this->texture.loadFromFile(this->texturename);
		this->isloadtexture = true;
	}

	if (!this->texture.loadFromFile(this->texturename)) {
		std::cout << "Image texture loading error" << std::endl;
	}
}

Image::Image()
{
	this->isloadtexture = false;
}

Image::~Image()
{

}

void Image::update(const float& dt)
{

}

void Image::updatetexture(std::string texturename,float scale, int image_x, int image_y)
{
	this->texturename = texturename;

	this->inittexture();

	this->sprite.setTexture(this->texture);
	this->sprite.setScale(scale, scale);
	this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	this->sprite.setPosition(image_x, image_y);
}

void Image::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
