#include "Cat.h"
#include <iostream>


int TILESIZE = 64;


Cat::Cat(sf::Texture *texture, gridvector position, int ID, SoundHandler *soundhandler) : GameObject(),
mID(ID),
mCoord(position),
mSpeed(2),
mAbilityTime(sf::seconds(5)),
mSoundHandler(soundhandler),
mAnimationhandler(64, 64, &mSprite){
	mSprite.setTexture(*texture, true);
	mSprite.setTextureRect(sf::IntRect(1, 1, 64, 64));
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
			mPosition.y -= (1 * mSpeed);
			mAnimationhandler.animation(1,6);
		}
		else if (direction == 3 && mPosition.y != newPos.y) {
			mPosition.y += (1 * mSpeed);
			mAnimationhandler.animation(0, 6);
		}
		else if (direction == 2 && mPosition.x != newPos.x) {
			mPosition.x -= (1 * mSpeed);
			mAnimationhandler.animation(3, 6);
			
		}
		else if (direction == 1 && mPosition.x != newPos.x) {
			mPosition.x += (1 * mSpeed);
			mAnimationhandler.animation(2, 6);
		}
		else {
			mMoving = false;
			mAnimationhandler.reset(direction);
			// säkrar att den håller rätt position
			if (direction == 4) {
				mCoord.y--;
				if (mPosition.y != newPos.y)
				mPosition.y = newPos.y;
			}
			if (direction == 3) {
				mCoord.y++;
				if (mPosition.y != newPos.y)
				mPosition.y = newPos.y;
			}
			if (direction == 2) {
				mCoord.x--;
				if (mPosition.x != newPos.x)
				mPosition.x = newPos.x;
			}
			if (direction == 1) {
				mCoord.x++;
				if (mPosition.x != newPos.x)
				mPosition.x = newPos.x;
			}
			if (mDashing){
				mSpeed = 2;
				mDashing = false;
			}
		}
	}
}

void Cat::moveForward(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 4;
		if (mGrid.isTilePassable(mCoord, gridvector(mCoord.x, mCoord.y - 1), tileLayer, Entities)){
			newPos.y = mPosition.y - 64;
			mSound.setBuffer(*mSoundHandler->GetSound(1));
			mSound.play();
			mMoving = true;
		}
	}
}
void Cat::moveBackWards(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 3;
		if (mGrid.isTilePassable(mCoord, gridvector(mCoord.x, mCoord.y + 1), tileLayer, Entities)){
			newPos.y = mPosition.y + 64;
			
			mMoving = true;
		}
	}
}
void Cat::moveLeft(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 2;
		if (mGrid.isTilePassable(mCoord, gridvector(mCoord.x - 1, mCoord.y), tileLayer, Entities)){
			newPos.x = mPosition.x - 64;
			
			mMoving = true;
		}
	}
}
void Cat::moveRight(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 1;
		if (mGrid.isTilePassable(mCoord, gridvector(mCoord.x + 1, mCoord.y), tileLayer, Entities)){
			newPos.x = mPosition.x + 64;

			mMoving = true;
			
		}
	}
}

void Cat::useAbility(TileLayer *tileLayer, std::vector<Entity*> *Entities){
	if (mID == 1){
		shadowDash(tileLayer,Entities);
	}
}

bool Cat::isInteracting(){
	return mInteracting;
}
bool Cat::isSolid(){
	return false;
}

//Returns position of sprite
sf::Vector2i Cat::GetPosition(){
	return mPosition;
}
gridvector Cat::getCoords(){
	return mCoord;
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

// SHADOW \\

void Cat::shadowDash(TileLayer *tileLayer, std::vector<Entity*> *Entities){
	std::cout << "DASH!" << std::endl;
	if (mAbilityClock.getElapsedTime()>=mAbilityTime && !mMoving){
		mDashing = true;

		if (direction == 1 && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x + 1, mCoord.y), tileLayer, Entities)) && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x + 2, mCoord.y), tileLayer, Entities))){
			mSpeed = mSpeed * 8;
			newPos.x = mPosition.x + 128;
			mCoord.x++;
			mMoving = true;
			mAbilityClock.restart();
		}
		if (direction == 2 && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x - 1, mCoord.y), tileLayer, Entities)) && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x - 2, mCoord.y), tileLayer, Entities))){
			mSpeed = mSpeed * 8;
			newPos.x = mPosition.x - 128;
			mCoord.x--;
			mMoving = true;
			mAbilityClock.restart();
		}
		if (direction == 3 && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x, mCoord.y + 1), tileLayer, Entities)) && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x, mCoord.y + 2), tileLayer, Entities))){
			mSpeed = mSpeed * 8;
			newPos.y = mPosition.y + 128;
			mCoord.y++;
			mMoving = true;
			mAbilityClock.restart();
		}
		if (direction == 4 && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x, mCoord.y - 1), tileLayer, Entities)) && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x, mCoord.y - 2), tileLayer, Entities))){
			mSpeed = mSpeed * 8;
			newPos.y = mPosition.y - 128;
			mCoord.y--;
			mMoving = true;
			mAbilityClock.restart();
		}
		
	}
	
}