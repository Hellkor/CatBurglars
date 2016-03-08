#ifndef INCLUDED_USABLE
#define INCLUDED_USABLE
#include "GameObject.h"

#include "Soundhandler.h"
class Usable : public GameObject{
public:
	Usable();
	~Usable();
	virtual void Render(sf::RenderWindow *mainWindow) = 0;
	virtual void Update(float dt) = 0;
	virtual sf::Vector2i GetPosition() = 0;
	virtual gridvector getCoords() = 0;
	virtual bool isInteracting() = 0;
	virtual bool getInteraction(GameObject *c) = 0;
	virtual int getChannelID() = 0;
	virtual Layer getLayer() = 0;
	virtual bool isSolid() = 0;


	
};

#endif