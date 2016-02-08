#include <iostream>
#include "SoundHandler.h"

using namespace std;

SoundHandler::SoundHandler(){
	/*sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Resources/sound.ogg"))
	{
		mSound.play();
		mSound.setLoop(true);
		
	}*/
}

SoundHandler::~SoundHandler(){

}

void SoundHandler::startMusic(){
	mMusic.openFromFile("Resources/sound.ogg");
	mMusic.play();
	std::cout << "saddsa" << std::endl;
}
