#ifndef INCLUDED_COLLECTIBLE
#define INCLUDED_COLLECTIBLE

#include "GameObject.h"
#include "gridvector.h"
#include "Cat.h"
class Collectible : public GameObject{
public:

	Collectible(sf::Texture *texture, gridvector position, bool collected);
	~Collectible();
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition();
	virtual gridvector getCoords();

	virtual bool isInteracting();
	virtual bool isSolid();

	bool getInteraction(Cat *cat);

private:
	sf::Sprite mSprite;
	sf::Vector2i mPosition;
	gridvector mCoords;
	bool mCollected;
};



#endif