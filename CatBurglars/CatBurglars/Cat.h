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
	virtual void move(int x, int y);
	virtual sf::Vector2i GetPosition();

	void moveForward();
	void moveBackWards();
	void moveLeft();
	void moveRight();

private:
	sf::Sprite mSprite;
	int mID;
	sf::Vector2i mPosition;
	gridvector mCoord;

	sf::Vector2i newPos;

	

	bool mMoving = false;

	int direction = 0;
};

#endif