#ifndef INCLUDED_SOUNDHANDLER
#define INCLUDED_SOUNDHANDLER

#include <SFML/Audio.hpp>
#include "GameObject.h"

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
	void initializeCat1(GameObject *cat1);
	void initializeCat2(GameObject *cat2);
	sf::SoundBuffer* getSound(int ID);
	int distanceSoundTest(GameObject *gameobject);

	
private:
	int mMusicVolume = 100;
	int mSoundVolume = 100;
	sf::SoundBuffer mBuffer, mBuffer2;
	sf::Sound mSound, mSound2;
	sf::Music mMusic;

	GameObject *mCat1;
	GameObject *mCat2;

	int pythagoras(int x, int y);
};

#endif