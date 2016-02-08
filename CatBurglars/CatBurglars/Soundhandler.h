#pragma once

#include <SFML/Audio.hpp>

class SoundHandler
{
public:
	SoundHandler();

	~SoundHandler();

	void startMusic();

private:
	sf::Sound mSound;
	sf::Music mMusic;
};

