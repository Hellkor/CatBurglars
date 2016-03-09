#include "Controller.h"
#include <iostream>
#include <SFML/Window.hpp>


Controller::Controller(CONTROLLER_TYPE controllertype):
C_TYPE(controllertype){
	assignKeys();
	
	if (C_TYPE == GamepadOne) {
		//isConnect();
	}
}

Controller::~Controller(){

}






void Controller::isConnect() {

	using namespace sf;
//	RenderWindow window;

	
	if (Joystick::isConnected(0)) {
		Joystick::Identification id = Joystick::getIdentification(0);
		std::cout << "\nnVendor ID: " << id.productId << std::endl;
		String controller("Joystick Use: " + id.name);
	//	window.setTitle(controller);
		unsigned int buttonCount = Joystick::getButtonCount(0);
		bool hasZ = Joystick::hasAxis(0, Joystick::Z);
		std::cout << "Button count: " << buttonCount << std::endl;
		std::cout << "Has a z-axis: " << hasZ << std::endl;
	}
	else {
		std::cout << "connect controlla\n";
	}
}


//Not used, delete if not needed
void Controller::assignController(int player, Cat *cat){
	if (player == 1)
	{
		mCat = cat;
	}
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
		dialogmanager->setSkipText("X-Butt");
		if (sf::Joystick::isButtonPressed(0, 2))
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
	
		#pragma endregion

		#pragma region "KB2"
		
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
		#pragma endregion

		#pragma region "GP1"

	case GamepadOne:

	
		float joyX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float joyY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		

		if (sf::Joystick::isButtonPressed(0, 0))
		{				//kolla knappN
			cat->useAbility(tileLayer, Entities);
		}
		if (joyY > 30.f)
		{
			cat->moveBackWards(tileLayer, Entities);
			
		}
		if (joyY < -30.f)
		{
			cat->moveForward(tileLayer, Entities);
		
		}
		if (joyX < -30.f)
		{
			cat->moveLeft(tileLayer, Entities);
		
		}
		if (joyX > 30.f)
		{
			cat->moveRight(tileLayer, Entities);
		
		}
		if (sf::Joystick::isButtonPressed(0, 4))
		{
			cat->mInteracting = true;
		}
		else
		{
			cat->mInteracting = false;
		}
		break;
		#pragma endregion

		#pragma region "GP2"

/*	case GamepadTwo:

		float joyX1 = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
		float joyY1 = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
	

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
		break;	*/
		#pragma endregion 
		
	}
}
