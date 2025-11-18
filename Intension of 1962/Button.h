#ifndef BUTTON_H
#define BUTTON_H

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

enum button_states{BTN_IDLE = 0,BTN_HOVER,BTN_ACTIVE};

class Button
{
private:
	short unsigned buttonstate;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idlecolor;
	sf::Color hovercolor;
	sf::Color activecolor;

public:
	Button(float x,float y,float width,float height,
		sf::Font* font,std::string text,
		sf::Color idlecolor,sf::Color hovercolor,sf::Color activecolor);
	virtual ~Button();

	//accessors
	const bool isPressed() const;

	//functions
	void update(const sf::Vector2f mousepos);
	void render(sf::RenderTarget* target);
};

#endif

