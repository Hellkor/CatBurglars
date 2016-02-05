#ifndef INCLUDED_CONTROLLER
#define INCLUDED_CONTROLLER

#include "Cat.h"
typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;
class Controller{

public:
	Controller();
	~Controller();
	void assignController(int player, Cat *cat);
	void move(Cat *cat, TileLayer *TileLayer, std::vector<Entity*> *Entities);
private:
	Cat *mCat;
};

#endif