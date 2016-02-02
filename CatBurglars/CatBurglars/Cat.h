#ifndef INCLUDED_CAT
#define INCLUDED_CAT

#include <SFML\Graphics.hpp>
#include "Player.h"

class Cat : public Player
{
public:
	Cat(sf::Texture *texture, int x, int y, int ID);
	~Cat();
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update();
	virtual void move(int x, int y);
	virtual sf::Vector2i GetPosition();
private:
	sf::Sprite mSprite;
	int mID;
	sf::Vector2i mPosition;
};

#endif