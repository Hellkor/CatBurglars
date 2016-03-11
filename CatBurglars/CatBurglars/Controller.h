#pragma once
#include <SFML/Graphics.hpp>
#include "Cat.h"
#include "DialogManager.h"

typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;
enum CONTROLLER_TYPE { KeyboardOne, KeyboardTwo, GamepadOne, GamepadTwo };

class Controller{

public:
	Controller(CONTROLLER_TYPE controllertype);
	~Controller();
	
	void move(Cat *cat, TileLayer *TileLayer, std::vector<Entity*> *Entities);

	void nextDialog(DialogManager *dialogManager);


private:

	Cat *mCat;
	
	CONTROLLER_TYPE C_TYPE;

	sf::Clock dialogClock;
	sf::Time dialogCooldown = sf::seconds(0.5);

	void assignKeys();
	bool isConnect(int i);

	sf::Keyboard::Key InteractionKey;
	

};

