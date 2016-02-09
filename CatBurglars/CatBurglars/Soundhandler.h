#ifndef INCLUDED_SOUNDHANDLER
#define INCLUDED_SOUNDHANDLER

#include <SFML/Audio.hpp>

class SoundHandler
{
public:
	SoundHandler();

	~SoundHandler();

	void Initialize();
	sf::SoundBuffer *GetSound(int ID);
	void startMusic(int ID);

private:
	sf::SoundBuffer mBuffer;
	sf::Music mMusic;
};

#endif