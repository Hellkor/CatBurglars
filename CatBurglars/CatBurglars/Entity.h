#ifndef INCLUDED_ENTITY
#define INCLUDED_ENTITY

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
enum Layer { BACK, MIDDLE , FRONT, OnWallUsables , DOORS };
class Entity
{
public:
	Entity();
	virtual ~Entity() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(sf::RenderWindow *mainWindow) = 0;
	virtual sf::Vector2i GetPosition()=0;
	virtual Layer getLayer() = 0;
protected:
};

#endif