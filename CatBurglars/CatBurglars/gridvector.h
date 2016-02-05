#pragma once

class gridvector{
public:
	gridvector(int xcoord, int ycoord) :
		x(xcoord),
		y(ycoord){

	}
	gridvector(gridvector &gridvector) :
		x(gridvector.x),
		y(gridvector.y){

	}
	gridvector() :
		x(0),
		y(0){

	}
	int x;
	int y;
	bool operator ==(gridvector pos){
		if (pos.x == x && pos.y == y){
			return true;
		}
		else return false;
	}
};