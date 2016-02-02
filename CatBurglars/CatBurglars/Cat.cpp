#include "Cat.h"
#include <iostream>

Cat::Cat(sf::Texture *texture, int x, int y, int ID) : Player(),
mID(ID)
{
	mSprite.setTexture(*texture, true);
	//Starting position
	mSprite.setPosition(x, y);
	mPosition.x = x;
	mPosition.y = y;
}
Cat::~Cat(){

}
//Render sprite on screen
void Cat::Render(sf::RenderWindow *mainWindow){
	mainWindow->draw(mSprite);
}

void Cat::Update(){
	
}
//Move the sprite
void Cat::move(int x, int y){
	//mSprite.move(x, y);
	mPosition.x += x;
	mPosition.y += y;
	mSprite.setPosition(sf::Vector2f(mPosition));
}
//Returns position of sprite
sf::Vector2i Cat::GetPosition(){
	return mPosition;
}