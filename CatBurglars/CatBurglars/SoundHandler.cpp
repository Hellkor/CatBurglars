#include <iostream>
#include "SoundHandler.h"

SoundHandler::SoundHandler()
{

}

SoundHandler::~SoundHandler()
{

}

void SoundHandler::Initialize()
{
	mBuffer.loadFromFile("Resources/Sounds/Fotsteg.ogg");
	mSound.setBuffer(mBuffer);
	mBuffer2.loadFromFile("Resources/Sounds/ahem.wav");
	mSound2.setBuffer(mBuffer2);
}

void SoundHandler::PlaySound(int ID)
{
	if (ID == 1) {
		if (!(mSound.getStatus() == sf::Sound::Playing)) {
			mSound.play();
		}
	}
	if (ID == 2) {	
		if (!(mSound2.getStatus() == sf::Sound::Playing)) {
			mSound2.play();
		}
	}
}

void SoundHandler::startMusic(int ID){
	if (ID == 1){
		mMusic.openFromFile("Resources/Sounds/sound.ogg");
		mMusic.setLoop(true);
		mMusic.play();
	}
}

void SoundHandler::stopMusic() {
	mMusic.stop();
}

void SoundHandler::setMusicVolume(int volume) {
	mMusicVolume = volume;
	mMusic.setVolume(volume);
}

void SoundHandler::setSoundVolume(int volume) {
	mSoundVolume = volume;
	/*mSound.setVolume(volume);
	mSound2.setVolume(volume);*/
}

void SoundHandler::initializeCat1(GameObject *cat1) {
	mCat1 = cat1;
}

void SoundHandler::initializeCat2(GameObject *cat2) {
	mCat2 = cat2;
}

sf::SoundBuffer* SoundHandler::getSound(int ID) {
	if (ID == 1) {
		return &mBuffer;
	}
	if (ID == 2) {
		return &mBuffer2;
	}
}

int SoundHandler::distanceSoundTest(GameObject *gameobject) {
	int newVolume = mSoundVolume;
	int x = mCat1->getCoords().x - gameobject->getCoords().x;
	int y = mCat1->getCoords().y - gameobject->getCoords().y;
	int x2=0;
	int y2=0;
	int length;
	//Check if not NULL
	if (mCat2 != 0) {
		x2 = mCat2->getCoords().x - gameobject->getCoords().x;
		y2 = mCat2->getCoords().y - gameobject->getCoords().y;
	}

	if (pythagoras(x,y) >= pythagoras(x2,y2)) {
		length = pythagoras(x, y);
	}
	else {
		length = (pythagoras(x2, y2));
	}

	if (length <-10 || length >10) {
		newVolume = 0;
	}
	if (length == -10 || length == 10) {
		newVolume = mSoundVolume * 0.1;
	}
	if (length == -9 || length == 9) {
		newVolume = mSoundVolume * 0.2;
	}
	if (length == -8 || length == 8) {
		newVolume = mSoundVolume * 0.3;
	}
	if (length == -7 || length == 7) {
		newVolume = mSoundVolume * 0.4;
	}
	if (length == -6 || length == 6) {
		newVolume = mSoundVolume * 0.5;
	}
	if (length == -5 || length == 5) {
		newVolume = mSoundVolume * 0.6;
	}
	if (length == -4 || length == 4) {
		newVolume = mSoundVolume * 0.7;
	}
	if (length == -3 || length == 3) {
		newVolume = mSoundVolume * 0.8;
	}
	if (length == -2 || length == 2) {
		newVolume = mSoundVolume * 0.9;
	}
	if (length == -1 || length == 1) {
		newVolume = mSoundVolume * 1;
	}
	//std::cout << "Volume set to: " <<newVolume << std::endl;
	return newVolume;
}

int SoundHandler::pythagoras(int x, int y) {
	int length;
	length = (sqrt((x * x) + (y * y)));
	return length;
}