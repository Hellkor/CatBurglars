#ifndef PATHNODE_H
#define PATHNODE_H

#include "gridvector.h"
#include <vector>

using namespace std;

struct PathValues
{
	int gCost, //Distance from starting Node.
		hCost, //Distance from end Node.
		fCost; //gCost + hCost.
};

class PathNode
{
public:
	PathNode(gridvector position, bool basePassable);
	~PathNode();
	gridvector GetGridVector();
	bool GetPassable();
	void SetPassable(bool passable);
	void ClearNeighbors();
	void SetNeighbor(PathNode *node);
	void SetPathValues(int gCost, int hCost);
	void SetPathParent(PathNode *parent);
	vector<PathNode*> GetNeighbors();
	gridvector GetGridPosition();
	PathValues GetPathValues();
	PathNode* GetPathParent();
	vector<PathNode*> GetPath(vector<PathNode*> path);
private:
	gridvector mGridVector;
	bool mPassable, mBasePassable;
	vector<PathNode*> mNeighborsVector;
	PathValues mPathValues;
	PathNode* mPathParent;
};

#endif