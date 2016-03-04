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
	//mVaktGår.setBuffer(mVaktGårB);

	mShadowDashB.loadFromFile("Resources/Sounds/ahem.wav");
	//mShadowDash.setBuffer(mShadowDashB);

	mSnowHaxB.loadFromFile("Resources/Sounds/Tangent.ogg");
	//mSnowHax.setBuffer(mSnowHaxB);

	mCratePushB.loadFromFile("Resources/Sounds/Putta.ogg");
	//mCratePush.setBuffer(mCratePushB);

	mDoorOpenB.loadFromFile("Resources/Sounds/Dörr.ogg");
	//mDoorOpen.setBuffer(mDoorOpenB);
}

void SoundHandler::PlaySound(int ID)
{
/*	if (ID == 1) {
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
	}*/
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
}

void SoundHandler::initializeCat1(GameObject *cat1) {
	mCat1 = cat1;
}

void SoundHandler::initializeCat2(GameObject *cat2) {
	mCat2 = cat2;
}

sf::SoundBuffer* SoundHandler::getSound(int ID) {
	if (ID == 1) {
		return &mVaktGårB;
	}
	if (ID == 2) {
		return &mShadowDashB;
	}
	if (ID == 3) {
		return &mSnowHaxB;
	}
	if (ID == 4) {
		return &mCratePushB;
	}
	if (ID == 5) {
		return &mDoorOpenB;
	}
}

int SoundHandler::distanceSound(GameObject *gameobject) {
	int newVolume = mSoundVolume;
	int x = mCat1->getCoords().x - gameobject->getCoords().x;
	int y = mCat1->getCoords().y - gameobject->getCoords().y;
	int x2 = 0;
	int y2 = 0;
	int length;
	//Check if not NULL
	if (mCat2 != 0) {
		x2 = mCat2->getCoords().x - gameobject->getCoords().x;
		y2 = mCat2->getCoords().y - gameobject->getCoords().y;
		if (pythagoras(x, y) <= pythagoras(x2, y2)) {
			length = pythagoras(x, y);
		}
		else {
			length = (pythagoras(x2, y2));
		}
	}
	else {
		length = pythagoras(x, y);
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
	return newVolume;
}

int SoundHandler::pythagoras(int x, int y) {
	int length;
	length = (sqrt((x * x) + (y * y)));
	return length;
}