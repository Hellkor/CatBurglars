#ifndef INCLUDED_CAT
#define INCLUDED_CAT

#include <SFML\Graphics.hpp>
#include "GameObject.h"

class Cat : public GameObject
{
public:
	Cat(sf::Texture *texture, gridvector v, int ID);
	~Cat();
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition();

	void moveForward();
	void moveBackWards();
	void moveLeft();
	void moveRight();

	bool isInteracting = false;
	bool interacting();
	bool isMoving();
	bool isColliding();

	int getDirection();

	void Collide();
	
private:
	float mSpeed;
	sf::Sprite mSprite;
	int mID;
	sf::Vector2i mPosition;
	gridvector mCoord;

	sf::Vector2i newPos;

	bool mMoving = false;
	bool mColliding = false;

	int direction = 0;
};

#endif