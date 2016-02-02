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
	virtual void Update();
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

	sf::Clock c;
	sf::Time animateTime;
	// KORREKT ANVÄNDNING = animationtime / moveInterval måste vara samma som TILESTORLEK
	sf::Time animationInterval = sf::milliseconds(512);
	sf::Time moveInterval = sf::milliseconds(8);

	sf::Clock moveClock;
	sf::Time moveTime;

	bool mMoving = false;

	int direction = 1;
};

#endif