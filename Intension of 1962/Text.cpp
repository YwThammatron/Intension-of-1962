#include "Text.h"

void Text::initfont()
{
	if (!this->font.loadFromFile(this->fontname)) {
		std::cout << "Font loading error" << std::endl;
	}
}

Text::Text(std::string fontname,std::string string, sf::Color color, unsigned int size,int x,int y)
{
	this->fontname = fontname;
	this->string = string;
	this->initfont();
	this->text.setFont(this->font);
	this->text.setString(this->string);
	this->text.setCharacterSize(size);
	this->text.setFillColor(color);
	//this->text.setOrigin(this->text.getGlobalBounds().width/2, this->text.getGlobalBounds().height / 2);

	this->text.setPosition(x, y);
}

Text::~Text()
{

}

void Text::update(std::string string)
{
	this->updatestring(string);
}

void Text::updatestring(std::string string)
{
	this->string = string;
	this->text.setString(this->string);
}

void Text::initcolor(sf::Color color)
{
	this->text.setFillColor(color);
}

void Text::render(sf::RenderTarget* target)
{
	target->draw(this->text);
}
