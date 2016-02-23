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

void SoundHandler::distanceSound(int ID, GameObject *gameobject) {
	int newVolume = mSoundVolume;
	int x;
	int y;
	//std::cout << gameobject->getCoords().x << std::endl;
	if ((-10 > (gameobject->getCoords().x - mCat1->getCoords().x) > 10) || (-10 >(gameobject->getCoords().y - mCat1->getCoords().y) > 10 )) {
		newVolume = 0;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 10) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -10) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 10) || (gameobject->getCoords().y - mCat1->getCoords().y) == -10)) {

		//std::cout << "DistanceVolume of guard 10 :" << newVolume << std::endl;
		newVolume = mSoundVolume * 0.1;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 9) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -9) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 9) || (gameobject->getCoords().y - mCat1->getCoords().y) == -9)) {

		//std::cout << "DistanceVolume of guard 9 :" << newVolume << std::endl;
		newVolume = mSoundVolume * 0.2;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 8) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -8) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 8) || (gameobject->getCoords().y - mCat1->getCoords().y) == -8)) {

		//std::cout << "DistanceVolume of guard 8 :" << newVolume << std::endl;
		newVolume = mSoundVolume * 0.3;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 7) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -7) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 7) || (gameobject->getCoords().y - mCat1->getCoords().y) == -7)) {

		//std::cout << "DistanceVolume of guard 7 :" << newVolume << std::endl;
		newVolume = mSoundVolume * 0.4;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 6) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -6) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 6) || (gameobject->getCoords().y - mCat1->getCoords().y) == -6)) {

		//std::cout << "DistanceVolume of guard 6 :" << newVolume << std::endl;
		newVolume = mSoundVolume * 0.5;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 5) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -5) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 5) || (gameobject->getCoords().y - mCat1->getCoords().y) == -5)) {

		//std::cout << "DistanceVolume of guard 5 :" << newVolume << std::endl;
		newVolume = mSoundVolume * 0.6;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 4) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -4) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 4) || (gameobject->getCoords().y - mCat1->getCoords().y) == -4)) {

		//std::cout << "DistanceVolume of guard 4 :" << newVolume << std::endl;
		newVolume = mSoundVolume * 0.7;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 3) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -3) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 3) || (gameobject->getCoords().y - mCat1->getCoords().y) == -3)) {

		//std::cout << "DistanceVolume of guard 3 :" << newVolume << std::endl;
		newVolume = mSoundVolume * 0.8;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 2) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -2) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 2) || (gameobject->getCoords().y - mCat1->getCoords().y) == -2)) {

		//std::cout << "DistanceVolume of guard 2 :" << newVolume << std::endl;
		newVolume = mSoundVolume * 0.9;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 1) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -1) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 1) || (gameobject->getCoords().y - mCat1->getCoords().y) == -1)) {
		//std::cout << "DistanceVolume of guard 1 :" << newVolume << std::endl;
		newVolume = mSoundVolume * 1;
	}
	if (ID == 1) {
		//std::cout << "DistanceVolume of guard :" << newVolume << std::endl;
	//	mSound.setVolume(newVolume);
		mMusic.setVolume(newVolume);
	}
	if (ID == 2) {
		mSound2.setVolume(newVolume);
	}
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
	//std::cout << gameobject->getCoords().x << std::endl;
	if ((10<x<-10) || (10<y<-10)) {
		newVolume = 0;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 10) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -10) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 10) || (gameobject->getCoords().y - mCat1->getCoords().y) == -10)) {


		newVolume = mSoundVolume * 0.1;
		std::cout << "DistanceVolume of guard 10 :" << newVolume << std::endl;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 9) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -9) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 9) || (gameobject->getCoords().y - mCat1->getCoords().y) == -9)) {


		newVolume = mSoundVolume * 0.2;
		std::cout << "DistanceVolume of guard 9 :" << newVolume << std::endl;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 8) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -8) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 8) || (gameobject->getCoords().y - mCat1->getCoords().y) == -8)) {

	
		newVolume = mSoundVolume * 0.3;
		std::cout << "DistanceVolume of guard 8 :" << newVolume << std::endl;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 7) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -7) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 7) || (gameobject->getCoords().y - mCat1->getCoords().y) == -7)) {

		newVolume = mSoundVolume * 0.4;

		std::cout << "DistanceVolume of guard 7 :" << newVolume << std::endl;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 6) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -6) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 6) || (gameobject->getCoords().y - mCat1->getCoords().y) == -6)) {


		newVolume = mSoundVolume * 0.5;
		std::cout << "DistanceVolume of guard 6 :" << newVolume << std::endl;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 5) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -5) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 5) || (gameobject->getCoords().y - mCat1->getCoords().y) == -5)) {

		newVolume = mSoundVolume * 0.6;

		std::cout << "DistanceVolume of guard 5 :" << newVolume << std::endl;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 4) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -4) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 4) || (gameobject->getCoords().y - mCat1->getCoords().y) == -4)) {


		newVolume = mSoundVolume * 0.7;
		std::cout << "DistanceVolume of guard 4 :" << newVolume << std::endl;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 3) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -3) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 3) || (gameobject->getCoords().y - mCat1->getCoords().y) == -3)) {


		newVolume = mSoundVolume * 0.8;
		std::cout << "DistanceVolume of guard 3 :" << newVolume << std::endl;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 2) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -2) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 2) || (gameobject->getCoords().y - mCat1->getCoords().y) == -2)) {


		newVolume = mSoundVolume * 0.9;
		std::cout << "DistanceVolume of guard 2 :" << newVolume << std::endl;
	}
	if (((gameobject->getCoords().x - mCat1->getCoords().x) == 1) || ((gameobject->getCoords().x - mCat1->getCoords().x) == -1) || (((gameobject->getCoords().y - mCat1->getCoords().y) == 1) || (gameobject->getCoords().y - mCat1->getCoords().y) == -1)) {

		newVolume = mSoundVolume * 1;
		std::cout << "DistanceVolume of guard 1 :" << newVolume << std::endl;
	}
//	std::cout << newVolume << std::endl;
	return newVolume;
}