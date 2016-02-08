#ifndef INCLUDED_CRATE
#define INCLUDED_CRATE

#include "GameObject.h"
#include "Cat.h"

class Crate : public GameObject{
public:

	Crate(sf::Texture *texture, gridvector v, int ID);
	~Crate();
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition();
	virtual bool isSolid();
	void moveForward(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	void moveBackWards(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	void moveLeft(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	void moveRight(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	virtual bool isInteracting();
	bool getInteraction(Cat *c);

	gridvector getCoords();

private:
	sf::Sprite mSprite;
	sf::Vector2i mPosition;
	gridvector mCoord;

	bool mSolid;
	sf::Vector2i newPos;

	sf::Clock c;
	sf::Time animateTime;
	// KORREKT ANVÄNDNING = animationtime / moveInterval måste vara samma som TILESTORLEK
	sf::Time animationInterval = sf::milliseconds(512);
	sf::Time moveInterval = sf::milliseconds(8);
	Grid mGrid;
	int mID;

	bool mMoving = false;

	int direction = 0;
};



#endif