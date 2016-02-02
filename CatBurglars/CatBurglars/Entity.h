#ifndef INCLUDED_ENTITY
#define INCLUDED_ENTITY

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Entity
{
public:
	Entity();
	~Entity();
	virtual void Update(float dt) = 0;
	virtual void Render(sf::RenderWindow *mainWindow) = 0;
	virtual sf::Vector2i GetPosition()=0;
protected:
};

#endif