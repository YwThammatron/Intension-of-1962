#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idlecolor, sf::Color hovercolor, sf::Color activecolor)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width,height));

	//Set font
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(30);
	this->text.setPosition(sf::Vector2f(
		this->shape.getPosition().x + this->shape.getGlobalBounds().width/2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getGlobalBounds().height/2.f - this->text.getGlobalBounds().height / 2.f - 10
	));


	//Set button color
	this->idlecolor = idlecolor;
	this->hovercolor = hovercolor;
	this->activecolor = activecolor;

	this->shape.setFillColor(this->idlecolor);

	//Set button state
	this->buttonstate = BTN_IDLE;
	
}

Button::~Button()
{

}

//accessors

const bool Button::isPressed() const
{
	if (this->buttonstate == BTN_ACTIVE) {
		return true;
	}
	return false;
}

//functions

void Button::update(const sf::Vector2f mousepos)
{
	//Update the booleans for hover and pressed

	this->buttonstate = BTN_IDLE;

	//Hover if cursor hover button and not yet pressed
	if (this->shape.getGlobalBounds().contains(mousepos)) {
		this->buttonstate = BTN_HOVER;

		//Active if button is pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonstate = BTN_ACTIVE;
		}
	}

	switch (this->buttonstate) 
	{
	case BTN_IDLE:
		this->shape.setFillColor(idlecolor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(hovercolor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(activecolor);
		break;

	default:
		//Set Color if crashed
		this->shape.setFillColor(sf::Color::Black);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
	
}
