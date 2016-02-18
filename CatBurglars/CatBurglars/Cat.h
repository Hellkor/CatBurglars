#ifndef INCLUDED_CAT
#define INCLUDED_CAT

#include <SFML\Graphics.hpp>
#include "GameObject.h"
#include "Grid.h"
#include "AnimationHandler.h"

class Cat : public GameObject
{
	typedef vector<Tile*> TileRow;
	typedef vector<TileRow> TileLayer;
public:
	Cat(sf::Texture *texture, gridvector v, int ID, SoundHandler *soundhandler,int player);
	~Cat();
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition();
	virtual gridvector getCoords();

	void moveForward(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	void moveBackWards(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	void moveLeft(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	void moveRight(TileLayer *tileLayer, std::vector<Entity*> *Entities);

	void Cat::useAbility(TileLayer *tileLayer, std::vector<Entity*> *Entities);

	bool mInteracting = false;
	virtual bool isInteracting();
	bool isMoving();
	bool isColliding();

	int getDirection();
	bool getDashing();
	void Collide();

	virtual bool isSolid();
	
	bool canPushCrate = true;

	void shadowDash(TileLayer *tileLayer, std::vector<Entity*> *Entities, int direc);

	bool snowHax();

	int getPlayerIndex();
	

private:
	float mSpeed;
	sf::Sprite mSprite;
	int mID;
	sf::Vector2i mPosition;
	gridvector mCoord;
	
	int mPlayerIndex;

	sf::Sound mSound;
	SoundHandler* mSoundHandler;

	sf::Vector2i newPos;

	bool mMoving = false;
	bool mColliding = false;
	bool mDashing = false;
	Grid mGrid;


	int direction = 0;

	sf::Clock mAbilityClock;
	sf::Time mAbilityTime;

	AnimationHandler mAnimationhandler;

};

#endif