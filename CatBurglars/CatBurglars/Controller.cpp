#include "Controller.h"
#include <iostream>

Controller::Controller(CONTROLLER_TYPE controllertype):
C_TYPE(controllertype){
	assignKeys();
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

float joyX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
float joyY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
float joyX1 = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
float joyY1 = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);



void Controller::assignKeys() {
	switch (C_TYPE)
	{
	case KeyboardOne:
		InteractionKey = sf::Keyboard::Space;
		break;
	case KeyboardTwo:
		InteractionKey = sf::Keyboard::RControl;
		break;
	case GamepadOne:

		break;
	case GamepadTwo:

		break;
	default:
		break;
	}
}
void Controller::nextDialog(DialogManager *dialogmanager) {


	switch (C_TYPE) {
		//Keyboard One (WASD)
	case KeyboardOne:
		dialogmanager->setSkipText("Space");
		if (sf::Keyboard::isKeyPressed(InteractionKey))
		{
			if (dialogClock.getElapsedTime().asSeconds() >= dialogCooldown.asSeconds()) {
				dialogClock.restart();
				dialogmanager->nextDialog();
			}
		}
		
		break;
		//Keyboard Two (Arrows)
	case KeyboardTwo:
		dialogmanager->setSkipText("LControl");
		if (sf::Keyboard::isKeyPressed(InteractionKey))
		{
			if (dialogClock.getElapsedTime().asSeconds() >= dialogCooldown.asSeconds()) {
				dialogClock.restart();
				dialogmanager->nextDialog();
			}
		}
		
	}
}
//Change position of cat with keyboard
void Controller::move(Cat *cat, TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	switch (C_TYPE) {
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
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			cat->moveLeft(tileLayer, Entities);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			cat->moveBackWards(tileLayer, Entities);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			cat->moveRight(tileLayer, Entities);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			cat->mInteracting = true;
		}
		else {
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
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			cat->moveLeft(tileLayer, Entities);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			cat->moveBackWards(tileLayer, Entities);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			cat->moveRight(tileLayer, Entities);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		{
			cat->mInteracting = true;
		}
		else {
			cat->mInteracting = false;
		}
		break;

	case GamepadOne:
		if (sf::Joystick::isButtonPressed(0, 1))
		{				//kolla knappN
			cat->useAbility(tileLayer, Entities);
		}
		if (joyY > 0)
		{
			cat->moveBackWards(tileLayer, Entities);
		}
		if (joyY < 0)
		{
			cat->moveForward(tileLayer, Entities);
		}
		if (joyX < 0)
		{
			cat->moveLeft(tileLayer, Entities);
		}
		if (joyX > 0)
		{
			cat->moveRight(tileLayer, Entities);
		}
		if (sf::Joystick::isButtonPressed(0, 2))
		{
			cat->mInteracting = true;
		}
		else
		{
			cat->mInteracting = false;
		}
		break;

	case GamepadTwo:
		if (sf::Joystick::isButtonPressed(1, 1))
		{				//kolla knappN
			cat->useAbility(tileLayer, Entities);
		}
		if (joyY1 > 0)
		{
			cat->moveBackWards(tileLayer, Entities);
		}
		if (joyY1 < 0)
		{
			cat->moveForward(tileLayer, Entities);
		}
		if (joyX1 < 0)
		{
			cat->moveLeft(tileLayer, Entities);
		}
		if (joyX1 > 0)
		{
			cat->moveRight(tileLayer, Entities);
		}
		if (sf::Joystick::isButtonPressed(1, 2))
		{
			cat->mInteracting = true;
		}
		else
		{
			cat->mInteracting = false;
		}
		break;
	}
}