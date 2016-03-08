#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Tile.h"
#include "PathNode.h"
#include "GameObject.h"
#include "Cat.h"

using namespace std;

typedef vector<PathNode*> NodeRow;
typedef vector<NodeRow> NodeMap;

class Pathfinder
{
public:
	Pathfinder(vector<vector<Tile*>> *tileLayer);
	~Pathfinder();
	void Update(vector<Entity*> *entities);
	vector<PathNode*> FindPath(PathNode *startNode, PathNode *targetNode);
	int GetDistanceCost(PathNode *tile1, PathNode *tile2);
	int CheckPathLength(PathNode *tile, int oldLength);
	void UpdateEntities(vector<Entity*> *entities);
private:
	NodeMap mNodeMap;
	Grid mGrid;
};

#endif