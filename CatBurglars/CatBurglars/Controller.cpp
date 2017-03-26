#include "Controller.h"
#include <iostream>
#include <SFML/Window.hpp>


bool Keyboard1Occupied = false;
bool Keyboard2Occupied = false;

sf::Event event;

Controller::Controller(CONTROLLER_TYPE controllertype):
C_TYPE(controllertype){
	assignKeys();
	
}
Controller::Controller() {
	

}

Controller::~Controller(){

}






bool Controller::isConnect(int i) {
	if (i == 0) {
		if (sf::Joystick::isConnected(0)) {
			return true;
		}
		else return false;
	}
	if (i == 1) {
		if (sf::Joystick::isConnected(1)) {
			return true;
		}
		else return false;
	}
	
	return false;
	
}





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
		dialogmanager->setSkipText("RControl");
		if (sf::Keyboard::isKeyPressed(InteractionKey))
		{
			if (dialogClock.getElapsedTime().asSeconds() >= dialogCooldown.asSeconds()) {
				dialogClock.restart();
				dialogmanager->nextDialog();
			}
		}
	case GamepadOne:
		dialogmanager->setSkipText("X-Button");
		if (sf::Joystick::isButtonPressed(0, 2))
		{
			if (dialogClock.getElapsedTime().asSeconds() >= dialogCooldown.asSeconds()) {
				dialogClock.restart();
				dialogmanager->nextDialog();
			}
		}
	case GamepadTwo:
		dialogmanager->setSkipText("X-Button");
		if (sf::Joystick::isButtonPressed(1, 2))
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

#pragma region"KB1"

		//Keyboard One (WASD)

	case KeyboardOne:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			cat->useAbility(tileLayer, Entities);
		}
		else {
			cat->mInteracting = false;
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
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			cat->mInteracting = true;
		}
		else {
			cat->mInteracting = false;
		}*/
		break;

#pragma endregion

#pragma region "KB2"

		//Keyboard Two (Arrows)
	case KeyboardTwo:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			cat->useAbility(tileLayer, Entities);
		}
		else {
			cat->mInteracting = false;
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
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		{
			cat->mInteracting = true;
		}
		else {
			cat->mInteracting = false;
		}*/
		break;
#pragma endregion

#pragma region "GP1"



	case GamepadOne:
	{


		float joyX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float joyY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		float joyDPX = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
		float joyDPY = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);

		if (sf::Joystick::isButtonPressed(0, 0))
		{				//kolla knappN
			cat->useAbility(tileLayer, Entities);
		}
		else
		{
			cat->mInteracting = false;
		}
		
		if (joyY > 20.f || joyDPY < -15.f)
			{
				cat->moveBackWards(tileLayer, Entities);
			}
		else if (joyY < -20.f || joyDPY >15.f)
			{
				cat->moveForward(tileLayer, Entities);
			}
		else if (joyX < -20.f || joyDPX < -15.f)
			{
				cat->moveLeft(tileLayer, Entities);
			}
		else if (joyX > 20.f || joyDPX > 15.f )
			{
				cat->moveRight(tileLayer, Entities);
			}
	/*	if (sf::Joystick::isButtonPressed(0, 2))
		{
			cat->mInteracting = true;
		}
		else
		{
			cat->mInteracting = false;
		}*/
		
		break;
	}
#pragma endregion

#pragma region "GP2"

		

	case GamepadTwo:
	{
		
		float joyX1 = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
		float joyY1 = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
		float joyDPX1 = sf::Joystick::getAxisPosition(1, sf::Joystick::PovX);
		float joyDPY1 = sf::Joystick::getAxisPosition(1, sf::Joystick::PovY);

		if (sf::Joystick::isButtonPressed(1, 0))
		{				//kolla knappN
			cat->useAbility(tileLayer, Entities);
		}
		else
		{
			cat->mInteracting = false;
		}
		if (joyY1 > 20.f || joyDPY1 < -15.f)
		{
			cat->moveBackWards(tileLayer, Entities);
		}
		else if (joyY1 < -20.f || joyDPY1 > 15.f)
		{
			cat->moveForward(tileLayer, Entities);
		}
		else if (joyX1 < -20.f || joyDPX1<-15.f)
		{
			cat->moveLeft(tileLayer, Entities);
		}
		else if (joyX1 > 20.f || joyDPX1 >15.f)
		{
			cat->moveRight(tileLayer, Entities);
		}
		/*if (sf::Joystick::isButtonPressed(1, 2))
		{
			cat->mInteracting = true;
		}
		else
		{
			cat->mInteracting = false;
		}
		*/
		break;
	}

#pragma endregion 

	}
}

