#include <iostream>
#include "SoundHandler.h"

using namespace std;

SoundHandler::SoundHandler(){
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("CB MT 2.0.wav"))
	{
		mSound.play();
		mSound.setLoop(true);
		
	}
}
