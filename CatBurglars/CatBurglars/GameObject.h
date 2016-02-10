#ifndef INCLUDED_GAMEOBJECT
#define INCLUDED_GAMEOBJECT

#include <iostream>
#include <vector>
#include "Entity.h"
#include "gridvector.h"
#include "Soundhandler.h"

class GameObject : public Entity
{
public:
	GameObject();
	~GameObject();
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition() = 0;

	virtual bool isInteracting() = 0;

	virtual bool isSolid() = 0;

private:

};

#endif