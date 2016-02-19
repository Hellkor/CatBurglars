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
	mSound.setVolume(volume);
	mSound2.setVolume(volume);
}