#ifndef PATHNODE_H
#define PATHNODE_H

#include "gridvector.h"

class PathNode
{
public:
	PathNode(gridvector position, bool basePassable);
	~PathNode();
	gridvector GetGridVector();
	bool GetPassable();
	void SetPassable(bool passable);
private:
	gridvector mGridVector;
	bool mPassable;
};

#endif