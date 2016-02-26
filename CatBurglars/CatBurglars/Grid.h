#ifndef INCLUDED_GRID
#define INCLUDED_GRID

#include "Tile.h"
#include "gridvector.h"
#include "GameObject.h"
typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;

class Grid{
public:
	Grid();
	bool isTilePassable(GameObject *gameobject,gridvector position, TileLayer *Tiles,std::vector<Entity*> *Entities);
	bool canCrateMove(gridvector position, TileLayer *Tiles, std::vector<Entity*> *Entities);
	bool canCatDash(gridvector originalpos, gridvector position, TileLayer *Tiles, std::vector<Entity*> *Entities);
private:

};

#endif