#include <iostream>
#include "SoundHandler.h"

using namespace std;

SoundHandler::SoundHandler(){
	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile("Resources/Sounds/CB MT 2.0.wav"))
	{
		
		
	}
	else{
		mSound.setBuffer(buffer);
		mSound.play();
		mSound.setLoop(true);
	}
}
