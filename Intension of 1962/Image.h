#ifndef IMAGE_H
#define IMAGE_H

#include "Entity.h"

class Image
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::string texturename;

	bool isloadtexture;

	void inittexture();

public:
	Image();
	virtual ~Image();

	void update(const float& dt);
	void updatetexture(std::string texturename,float scale,int image_x, int image_y);
	void render(sf::RenderTarget* target = nullptr);
};

#endif

