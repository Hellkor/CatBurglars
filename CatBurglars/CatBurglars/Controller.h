#ifndef INCLUDED_CONTROLLER
#define INCLUDED_CONTROLLER

#include "Cat.h"
typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;
enum CONTROLLER_TYPE { KeyboardOne, KeyboardTwo, GamepadOne, GamepadTwo };
class Controller{

public:
	Controller(CONTROLLER_TYPE controllertype);
	~Controller();
	void assignController(int player, Cat *cat);
	void move(Cat *cat, TileLayer *TileLayer, std::vector<Entity*> *Entities);
private:
	Cat *mCat;
	
	CONTROLLER_TYPE C_TYPE;

};

#endif