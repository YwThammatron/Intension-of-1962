#ifndef TEXT_H
#define TEXT_H

#include "Entity.h"

class Text
{
private:

	sf::Font font;
	std::string fontname;

	void initfont();

public:
	
	sf::Text text;
	std::string string;

	void initcolor(sf::Color color);

	Text(std::string fontname, std::string string, sf::Color color, unsigned int size,int x,int y);
	virtual ~Text();

	void update(std::string string);
	void updatestring(std::string string);
	
	void render(sf::RenderTarget* target = nullptr);
};

#endif

