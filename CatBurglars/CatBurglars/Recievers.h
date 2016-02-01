#pragma once

#include "GameObject.h"

class Recievers : public GameObject{
public:
	Recievers(){ }
	~Recievers(){ }
	virtual void connectToChannel(int channelID) = 0;
	virtual void checkChannel()= 0;
private:

};