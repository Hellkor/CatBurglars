#ifndef INCLUDED_SOUNDHANDLER
#define INCLUDED_SOUNDHANDLER

#include <SFML/Audio.hpp>

class SoundHandler
{
public:
	SoundHandler();

	~SoundHandler();

	void Initialize();
	void PlaySound(int ID);
	void startMusic(int ID);
	void stopMusic();
	void setMusicVolume(int volume);
	void setSoundVolume(int volume);
private:
	int mMusicVolume = 100;
	int mSoundVolume = 100;
	sf::SoundBuffer mBuffer, mBuffer2;
	sf::Sound mSound, mSound2;
	sf::Music mMusic;
};

#endif