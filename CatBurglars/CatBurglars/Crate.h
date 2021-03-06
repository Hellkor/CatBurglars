#ifndef INCLUDED_CRATE
#define INCLUDED_CRATE

#include "GameObject.h"
#include "Cat.h"
#include "Soundhandler.h"
class Crate : public GameObject{
public:

	Crate(sf::Texture *texture, gridvector v, int ID, SoundHandler *soundhandler, bool movable);
	virtual ~Crate();
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition();
	virtual gridvector getCoords();
	virtual bool isSolid();
	bool moveForward(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	bool moveBackWards(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	bool moveLeft(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	bool moveRight(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	virtual bool isInteracting();
	bool getInteraction(Cat *c);
	virtual Layer getLayer();
	void interaction(Usable *usable);

private:
	sf::Sprite mSprite;
	sf::Vector2i mPosition;
	gridvector mCoord;

	bool mSolid;
	sf::Vector2i newPos;

	sf::Clock c;
	sf::Time animateTime;
	// KORREKT ANV�NDNING = animationtime / moveInterval m�ste vara samma som TILESTORLEK
	sf::Time animationInterval = sf::milliseconds(512);
	sf::Time moveInterval = sf::milliseconds(8);
	Grid mGrid;
	int mID;

	bool mMoving = false;
	bool mMoveable = false;

	int direction = 0;

	SoundHandler* mSoundHandler;
	sf::Sound mCrateMoving;
};



#endif