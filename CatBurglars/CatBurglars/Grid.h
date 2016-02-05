#ifndef INCLUDED_GRID
#define INCLUDED_GRID

#include "Tile.h"
#include "gridvector.h"
typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;

class Grid{
public:
	Grid();
	bool isTilePassable(gridvector originalpos,gridvector position, TileLayer *Tiles,std::vector<Entity*> *Entities);
	bool canCrateMove(gridvector position, TileLayer *Tiles, std::vector<Entity*> *Entities);

private:

};

#endif