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
	//mBuffer.loadFromFile("Resources/Sounds/ahem.wav");
}

sf::SoundBuffer* SoundHandler::GetSound(int ID)
{
	if (ID = 1){
		return &mBuffer;
	}
}

void SoundHandler::startMusic(int ID){
	if (ID == 1){
		mMusic.openFromFile("Resources/Sounds/sound.ogg");
		mMusic.play();
	}
}
