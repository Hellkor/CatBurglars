#include <iostream>
#include "SoundHandler.h"

static sf::SoundBuffer mVaktGårB, mShadowDashB, mSnowHaxB, mCratePushB, mDoorOpenB,mFailStinger;

SoundHandler::SoundHandler()
{

}

SoundHandler::~SoundHandler()
{

}

void SoundHandler::Initialize()
{
	mVaktGårB.loadFromFile("Resources/Sounds/Fotsteg.wav");


	mShadowDashB.loadFromFile("Resources/Sounds/dash.wav");


	mSnowHaxB.loadFromFile("Resources/Sounds/Tangent.wav");


	mCratePushB.loadFromFile("Resources/Sounds/crate.wav");


	mDoorOpenB.loadFromFile("Resources/Sounds/door.wav");

	mFailStinger.loadFromFile("Resources/Sounds/stinger_failure.ogg");

}

void SoundHandler::PlaySound(int ID)
{

}

void SoundHandler::startMusic(string ID){
		if (ID == "Menu") {
			mMusic.openFromFile("Resources/Music/maintheme.ogg");
			mMusic.setLoop(true);
			mMusic.play();
		}
		else if (ID == "1_1" || ID == "1_2") {
			mMusic.openFromFile("Resources/Music/level_1_1-2.ogg");
			mMusic.setLoop(true);
			mMusic.play();
		}
		else if (ID == "1_3") {
			mMusic.openFromFile("Resources/Music/level_1_3.ogg");
			mMusic.setLoop(true);
			mMusic.play();
		}
		else if (ID == "1_4") {
			mMusic.openFromFile("Resources/Music/level_1_4.ogg");
			mMusic.setLoop(true);
			mMusic.play();
		}
		else if (ID == "1_5") {
			mMusic.openFromFile("Resources/Music/level_1_5.ogg");
			mMusic.setLoop(true);
			mMusic.play();
		}
		else if (ID == "1_6") {
			mMusic.openFromFile("Resources/Music/level_1_6.ogg");
			mMusic.setLoop(true);
			mMusic.play();
		}
		else if (ID == "2_1") {
			mMusic.openFromFile("Resources/Music/level_2_1.ogg");
			mMusic.setLoop(true);
			mMusic.play();
		}
		else if (ID == "2_2" || ID == "2_3") {
			mMusic.openFromFile("Resources/Music/level_2_2.ogg");
			mMusic.setLoop(true);
			mMusic.play();
		}
		else if (ID == "flee1" || ID == "flee2" || ID == "flee3") {
			mMusic.openFromFile("Resources/Music/level_2_3.ogg");
			mMusic.setLoop(true);
			mMusic.play();
		}
		else {
			mMusic.openFromFile("Resources/Music/level_1_6.ogg");
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
	if (ID == 6) {
		return &mFailStinger;
	}
}

void SoundHandler::Clear() {
	mCat2 = nullptr;
}

int SoundHandler::distanceSound(GameObject *gameobject) {
	int newVolume = mSoundVolume;
	int x = mCat1->getCoords().x - gameobject->getCoords().x;
	int y = mCat1->getCoords().y - gameobject->getCoords().y;
	int x2 = 0;
	int y2 = 0;
	int length;
	//Check if not NULL
	if (mCat2 != nullptr) {
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

	if (length >10) {
		newVolume = 0;
	}
	else
		newVolume = mSoundVolume * (1-((length*0.1)-0.1));

	return newVolume;
}

int SoundHandler::pythagoras(int x, int y) {
	int length;
	length = (sqrt((x * x) + (y * y)));
	return length;
}

float SoundHandler::changeIndiVolume(float change) {
	return mSoundVolume * change;
}