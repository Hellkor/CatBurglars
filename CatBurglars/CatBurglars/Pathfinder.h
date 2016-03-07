#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Tile.h"

using namespace std;

typedef vector<PathNode*> NodeRow;
typedef vector<NodeRow> NodeMap;

class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();
	vector<PathNode*> FindPath(PathNode *startNode, PathNode *targetNode);
private:
	NodeMap mNodeMap;
};

#endif