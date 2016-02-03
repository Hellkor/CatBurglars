#include "Cat.h"
#include <iostream>

int TILESIZE = 64;

Cat::Cat(sf::Texture *texture, gridvector position, int ID) : GameObject(),
mID(ID),
mCoord(position),
mSpeed(2){
	mSprite.setTexture(*texture, true);
	//Starting position
	mPosition = sf::Vector2i(mCoord.x * 64, mCoord.y * 64);
}
Cat::~Cat(){

}
//Render sprite on screen
void Cat::Render(sf::RenderWindow *mainWindow){
	
	mSprite.setPosition((sf::Vector2f)mPosition);
	mainWindow->draw(mSprite);
}

void Cat::Update(float dt){


	if (mMoving){
		if (direction == 4 && mPosition.y != newPos.y) {
<<<<<<< HEAD
			mPosition.y -= 1 *mSpeed;
		}
		else if (direction == 3 && mPosition.y != newPos.y) {
			mPosition.y += 1 * mSpeed;
		}
		else if (direction == 2 && mPosition.x != newPos.x) {
			mPosition.x -= 1 * mSpeed;
			
		}
		else if (direction == 1 && mPosition.x != newPos.x) {
			mPosition.x += 1 * mSpeed;
=======
			mPosition.y -= 1;
		}
		else if (direction == 3 && mPosition.y != newPos.y) {
			mPosition.y += 1;
		}
		else if (direction == 2 && mPosition.x != newPos.x) {
			mPosition.x -= 1;

		}
		else if (direction == 1 && mPosition.x != newPos.x) {
			mPosition.x += 1;
>>>>>>> origin/master
		}
		else {
			mMoving = false;

			// säkrar att den håller rätt position
			if (direction == 4) {
				if (mPosition.y != newPos.y)
				mPosition.y = newPos.y;
			}
			if (direction == 3) {
				if (mPosition.y != newPos.y)
				mPosition.y = newPos.y;
			}
			if (direction == 2) {
				if (mPosition.x != newPos.x)
				mPosition.x = newPos.x;
			}
			if (direction == 1) {
				if (mPosition.x != newPos.x)
				mPosition.x = newPos.x;
			}
		}
	}
}

void Cat::moveForward() {
	if (!mMoving) {
		// if (!Grid.getTile(mCoords.x -1,mCoords.y)->isSolid())
		// do....
		newPos.y = mPosition.y - 64;
		direction = 4;
		mCoord.y --;
		mMoving = true;
	}
}
void Cat::moveBackWards() {
	if (!mMoving) {
		newPos.y = mPosition.y + 64;
		direction = 3;
		mCoord.y++;
		mMoving = true;
	}
}
void Cat::moveLeft() {
	if (!mMoving) {

		newPos.x = mPosition.x - 64;
		direction = 2;
		mCoord.x --;
		mMoving = true;
	}
}
void Cat::moveRight() {
	if (!mMoving) {
		newPos.x = mPosition.x + 64;
		direction = 1;
		mCoord.x++;
		mMoving = true;
	}
}

bool Cat::interacting(){
	return isInteracting;
}


//Returns position of sprite
sf::Vector2i Cat::GetPosition(){
	return mPosition;
}

int Cat::getDirection(){
	return direction;
}

bool Cat::isMoving(){
	return mMoving;
}

bool Cat::isColliding(){
	return mColliding;
}

void Cat::Collide(){
	mColliding = true;
}