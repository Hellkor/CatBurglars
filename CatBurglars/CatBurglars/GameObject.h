#ifndef INCLUDED_GAMEOBJECT
#define INCLUDED_GAMEOBJECT

#include <iostream>
#include <vector>
#include "Entity.h"
#include "gridvector.h"

class GameObject : public Entity
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition() = 0;
	virtual gridvector getCoords() = 0;

	virtual bool isInteracting() = 0;

	virtual bool isSolid() = 0;

	virtual Layer getLayer() = 0;

private:

};

#endif