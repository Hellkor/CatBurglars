#include "Controller.h"
#include <iostream>

Controller::Controller(CONTROLLER_TYPE controllertype):
C_TYPE(controllertype){
	
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
void Controller::move(Cat *cat, TileLayer *tileLayer, std::vector<Entity*> *Entities){
	switch (C_TYPE){
		//Keyboard One (WASD)
	case KeyboardOne:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			cat->useAbility(tileLayer, Entities);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			cat->moveForward(tileLayer, Entities);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			cat->moveLeft(tileLayer, Entities);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			cat->moveBackWards(tileLayer, Entities);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			cat->moveRight(tileLayer, Entities);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			cat->mInteracting = true;
		}
		else{
			cat->mInteracting = false;
		}
		break;
		//Keyboard Two (Arrows)
	case KeyboardTwo:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			cat->useAbility(tileLayer, Entities);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			cat->moveForward(tileLayer, Entities);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			cat->moveLeft(tileLayer, Entities);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			cat->moveBackWards(tileLayer, Entities);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			cat->moveRight(tileLayer, Entities);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		{
			cat->mInteracting = true;
		}
		else{
			cat->mInteracting = false;
		}
		break;
	}
}