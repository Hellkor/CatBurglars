#include "PathNode.h"

PathNode::PathNode(gridvector position, bool basePassable)
	: mGridVector(position), mPassable(basePassable)
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
	return mPassable;
}

void PathNode::SetPassable(bool passable) { mPassable = passable; }
