#include <iostream>
#include "SoundHandler.h"

using namespace std;

SoundHandler::SoundHandler(){
	/*sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Resources/sound.ogg"))
	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile("Resources/Sounds/CB MT 2.0.wav"))
	{
		
		
	}
	else{
		mSound.setBuffer(buffer);
		mSound.play();
		mSound.setLoop(true);
		
	}*/
}

SoundHandler::~SoundHandler(){

}

void SoundHandler::startMusic(){
	mMusic.openFromFile("Resources/Sounds/sound.ogg");
	mMusic.play();
}
