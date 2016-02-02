#pragma once

#include "Tile.h"
#include "gridvector.h"

class Grid{
public:
	Grid(int WIDTH, int HEIGHT);

	/*
	Tile getTile(gridvector position){
		Tile *thisTile;
		for each (Tile *t in tiles){
			if (t->getGridCoord() == position){
				thisTile = t;
				return *thisTile;
			}
		}
		
	}
	*/

private:
	vector<Tile*> tiles;

};