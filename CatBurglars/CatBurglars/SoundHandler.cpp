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
	mVaktGårB.loadFromFile("Resources/Sounds/Fotsteg.ogg");
	mVaktGår.setBuffer(mVaktGårB);

	mShadowDashB.loadFromFile("Resources/Sounds/ahem.wav");
	mShadowDash.setBuffer(mShadowDashB);

	mSnowHaxB.loadFromFile("Resources/Sounds/Tangent.ogg");
	mSnowHax.setBuffer(mSnowHaxB);

	mCratePushB.loadFromFile("Resources/Sounds/Putta.ogg");
	mCratePush.setBuffer(mCratePushB);

	mDoorOpenB.loadFromFile("Resources/Sounds/Dörr.ogg");
	mDoorOpen.setBuffer(mDoorOpenB);
}

void SoundHandler::PlaySound(int ID)
{
	if (ID == 1) {
		if (!(mVaktGår.getStatus() == sf::Sound::Playing)) {
			mVaktGår.play();
		}
	}
	if (ID == 2) {	
		if (!(mShadowDash.getStatus() == sf::Sound::Playing)) {
			mShadowDash.play();
		}
	}
	if (ID == 3) {
		if (!(mSnowHax.getStatus() == sf::Sound::Playing)) {
			mSnowHax.play();
		}
	}
	if (ID == 4) {
		if (!(mCratePush.getStatus() == sf::Sound::Playing)) {
			mCratePush.play();
		}
	}
	if (ID == 5) {
		if (!(mDoorOpen.getStatus() == sf::Sound::Playing)) {
			mDoorOpen.play();
		}
	}
}

void SoundHandler::startMusic(int ID){
	if (ID == 1){
		mMusic.openFromFile("Resources/Sounds/sound.ogg");
		mMusic.setLoop(true);
		mMusic.play();
	}
	if (ID == 2) {
		mMusic.openFromFile("Resources/Sounds/CBF1R1v4.ogg");
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
	mVaktGår.setVolume(volume);
	mShadowDash.setVolume(volume);
	mSnowHax.setVolume(volume);
	mCratePush.setVolume(volume);
	mDoorOpen.setVolume(volume);
}