#ifndef SOUND_H
#define SOUND_H

#include "Entity.h"

class Sound
{
private:
	
	sf::SoundBuffer soundbuffer;

	void initbuffer();

public:
	Sound(std::string soundname,bool isloop,unsigned int volume);
	virtual ~Sound();

	sf::Sound sound;
	std::string soundname;
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

#endif

