#include "PathNode.h"

PathNode::PathNode(gridvector position, bool basePassable)
	: mGridVector(position), mBasePassable(basePassable)
{

}

PathNode::~PathNode()
{

}

gridvector PathNode::GetGridVector()
{
	return mGridVector;
}

bool PathNode::GetPassable()
{
	if (mBasePassable)
		return mPassable;
	else return false;
}

void PathNode::SetPassable(bool passable) { mPassable = passable; }

void PathNode::ClearNeighbors()
{
	mNeighborsVector.clear();
}

void PathNode::SetNeighbor(PathNode *node)
{
	mNeighborsVector.push_back(node);
}

void PathNode::SetPathValues(int gCost, int hCost)
{
	mPathValues.gCost = gCost;
	mPathValues.hCost = hCost;
	mPathValues.fCost = gCost + hCost;
}

void PathNode::SetPathParent(PathNode *parent)
{
	mPathParent = parent;
}

vector<PathNode*> PathNode::GetNeighbors()
{
	return mNeighborsVector;
}

gridvector PathNode::GetGridPosition()
{
	return mGridVector;
}

PathValues PathNode::GetPathValues()
{
	return mPathValues;
}

PathNode * PathNode::GetPathParent()
{
	return mPathParent;
}

vector<PathNode*> PathNode::GetPath(vector<PathNode*> path)
{
	if (mPathParent != nullptr)
	{
		path = mPathParent->GetPath(path);
		path.push_back(mPathParent);
	}
	return path;
}
