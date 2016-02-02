#include "Controller.h"
#include <iostream>

Controller::Controller()
{
	
}

Controller::~Controller(){

}

//Not used, delete if not needed
void Controller::assignController(int player, Cat *cat){
	if (player == 1)
	{
		mCat = cat;
	}
}

//Change position of cat with keyboard
void Controller::move(Cat *cat){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		cat->moveForward();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		cat->moveLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		cat->moveBackWards();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		cat->moveRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		cat->isInteracting = true;
	}
	else{
		cat->isInteracting = false;
	}
}