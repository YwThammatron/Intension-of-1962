#include "Sound.h"

void Sound::initbuffer()
{
	if (!this->soundbuffer.loadFromFile(this->soundname)) {
		std::cout << "Sound loading error" << std::endl;
	}
}

Sound::Sound(std::string soundname,bool isloop, unsigned int volume)
{
	this->soundname = soundname;
	this->initbuffer();

	this->sound.setBuffer(this->soundbuffer);
	this->sound.setLoop(isloop);
	this->sound.setVolume(volume);
}

Sound::~Sound()
{

}

void Sound::update(const float& dt)
{

}

void Sound::render(sf::RenderTarget* target)
{

}
