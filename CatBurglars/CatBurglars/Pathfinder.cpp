#include "Pathfinder.h"

Pathfinder::Pathfinder(vector<vector<Tile*>>* tileLayer)
{
	for (vector<vector<Tile*>>::size_type y = 0; y < tileLayer->size(); y++)
	{
		NodeRow row;
		for (vector<Tile*>::size_type x = 0; x < tileLayer->at(y).size(); x++)
		{
			PathNode *node;
			node = new PathNode(tileLayer->at(y)[x]->getCoords(), tileLayer->at(y)[x]->GetID() != 0);
			row.push_back(node);
		}
		mNodeMap.push_back(row);
	}
}

Pathfinder::~Pathfinder()
{

}

void Pathfinder::Update(vector<Entity*> *entities)
{
	for each (NodeRow r in mNodeMap)
		for each (PathNode* n in r)
			n->SetPassable(true);
	for each (Entity* e in *entities)
	{
		if (GameObject *o = dynamic_cast<GameObject*>(e))
		{
			if (o != dynamic_cast<Cat*>(o))
			{
				gridvector pos = o->getCoords();
				mNodeMap[pos.y][pos.x]->SetPassable(!o->isSolid);
			}
		}
	}
}

vector<PathNode*> Pathfinder::FindPath(PathNode * startNode, PathNode * targetNode)
{
	vector<PathNode*>
		open,			//Nodes whose F cost has been calculated.
		closed;			//Nodes that have been evaluated.
	startNode->SetPathValues(0, GetDistanceCost(startNode, targetNode));
	open.push_back(startNode);
	bool loop = true, failed = false;

	PathNode *current = startNode;
	while (loop && !failed)
	{
		if (open.size() == 0)
		{
			failed = true;
			break;
		}
		current = open[0];
		for (vector<PathNode*>::size_type i = 0; i < open.size(); i++)
		{
			if (open[i]->GetPathValues().fCost < current->GetPathValues().fCost)
				current = open[i];
		}

		open.erase(find(open.begin(), open.end(), current));

		closed.push_back(current);

		if (current == targetNode)
		{
			loop = false;
			break;
		}

		for each (PathNode* neighbor in current->GetNeighbors())
		{
			int newPathLength = CheckPathLength(current, 0);
			newPathLength += 10;

			if (!neighbor->GetPassable() || find(closed.begin(), closed.end(), neighbor) != closed.end())
				; //Skip
			else if (newPathLength < CheckPathLength(neighbor, 0) || find(open.begin(), open.end(), neighbor) == open.end())
			{
				neighbor->SetPathValues(newPathLength, GetDistanceCost(neighbor, targetNode));
				//if newPathLength == CheckPathLength(neighbor, 0) Put a random chance on this to create more random Paths.
				neighbor->SetPathParent(current);

				if (find(open.begin(), open.end(), neighbor) == open.end())
				{
					open.push_back(neighbor);
				}
			}
		}
	}

	vector<PathNode*> path;
	if (failed)
		cout << "No Path!" << endl;
	if (failed)
	{
		for each (PathNode* n in open)
		{
			n->SetPathParent(nullptr);
			n->SetPathValues(0, 0);
		}
		for each (PathNode* n in closed)
		{
			n->SetPathParent(nullptr);
			n->SetPathValues(0, 0);
		}
		return path;
	}
	path = current->GetPath(path);
	cout << path.size();

	for each (PathNode* n in open)
	{
		n->SetPathParent(nullptr);
		n->SetPathValues(0, 0);
	}
	for each (PathNode* n in closed)
	{
		n->SetPathParent(nullptr);
		n->SetPathValues(0, 0);
	}

	return path;
}

int Pathfinder::GetDistanceCost(PathNode *node1, PathNode *node2)
{
	int distanceCost, tile1X, tile1Y, tile2X, tile2Y;
	tile1X = node1->GetGridPosition().x;
	tile1Y = node1->GetGridPosition().y;
	tile2X = node2->GetGridPosition().x;
	tile2Y = node2->GetGridPosition().y;
	int xCost, yCost;
	xCost = tile1X - tile2X;
	xCost = abs(xCost);
	yCost = tile1Y - tile2Y;
	yCost = abs(yCost);
	distanceCost = (xCost + yCost) * 10;
	return distanceCost;
}

int Pathfinder::CheckPathLength(PathNode *tile, int oldLength)
{
	int length = oldLength;
	PathNode *parent = tile->GetPathParent();
	if (parent != nullptr)
	{
		length += 10;
		length = CheckPathLength(parent, length);
	}
	return length;
}

void Pathfinder::UpdateEntities(vector<Entity*> *entities)
{

}
