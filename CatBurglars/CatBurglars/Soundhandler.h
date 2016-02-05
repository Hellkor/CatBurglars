#pragma once

#include <SFML/Audio.hpp>

class SoundHandler
{
public:
	SoundHandler();

	~SoundHandler();

private:
	sf::Sound mSound;

};

