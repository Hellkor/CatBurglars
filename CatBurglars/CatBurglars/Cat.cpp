#include "Cat.h"
#include <iostream>

Cat::Cat(sf::Texture *texture, gridvector position, int ID) : GameObject(),
mID(ID),
mCoord(position){
	mSprite.setTexture(*texture, true);
	//Starting position
	mPosition = sf::Vector2i(mCoord.x * 64, mCoord.y * 64);
}
Cat::~Cat(){

}
//Render sprite on screen
void Cat::Render(sf::RenderWindow *mainWindow){
//	cout << mPosition.x << "  " << mPosition.y << endl;
	mSprite.setPosition((sf::Vector2f)mPosition);
	mainWindow->draw(mSprite);
}

void Cat::Update(){

	

	if (c.getElapsedTime() < animationInterval && mMoving) {

		if (moveClock.getElapsedTime() >= moveInterval) {

			moveClock.restart();
			if (direction == 4) {
				mPosition.y -= 1;
			}
			if (direction == 3) {
				mPosition.y += 1;
			}
			if (direction == 2) {
				mPosition.x -= 1;
			}
			if (direction == 1) {
				mPosition.x += 1;
			}
		}

	}
	else {  // BUG FIX // slutgiltiga positionen hamnar inte alltid på önskad position. så den korrigeras
		
		if (direction == 4) {
			mPosition.y = newPos.y;
		}
		if (direction == 3) {
			mPosition.y = newPos.y;
		}
		if (direction == 2) {
			mPosition.x = newPos.x;
		}
		if (direction == 1) {
			mPosition.x = newPos.x;
		}
		
		mMoving = false;
	}

}

void Cat::moveForward() {
	if (!mMoving) {
		// if (!Grid.getTile(mCoords.x -1,mCoords.y)->isSolid())
		// do....
		newPos.y = mPosition.y - 64;
		direction = 4;
		c.restart();
		mCoord.y --;
		mMoving = true;
	}
}
void Cat::moveBackWards() {
	if (!mMoving) {
		newPos.y = mPosition.y + 64;
		direction = 3;
		c.restart();
		mCoord.y++;
		mMoving = true;
	}
}
void Cat::moveLeft() {
	if (!mMoving) {

		newPos.x = mPosition.x - 64;
		direction = 2;
		c.restart();
		mCoord.x --;
		mMoving = true;
	}
}
void Cat::moveRight() {
	if (!mMoving) {
		newPos.x = mPosition.x + 64;
		direction = 1;
		c.restart();
		mCoord.x++;
		mMoving = true;
	}
}

bool Cat::interacting(){
	return isInteracting;
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