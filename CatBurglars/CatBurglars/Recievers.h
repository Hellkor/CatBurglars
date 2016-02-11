#pragma once

#include "GameObject.h"

class Recievers : public GameObject{
public:
	Recievers(){ }
	~Recievers(){ }
	virtual void connectToChannel(int channelID) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(sf::RenderWindow *window) = 0;
	virtual sf::Vector2i GetPosition() = 0;
	virtual gridvector getCoords() = 0;
	virtual bool isSolid() = 0;
	virtual bool isInteracting() = 0;
private:


};