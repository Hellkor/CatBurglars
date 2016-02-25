#include "Cat.h"
#include <iostream>


int TILESIZE = 64;


Cat::Cat(sf::Texture *texture, gridvector position, int ID, SoundHandler *soundhandler,int player) : GameObject(),
mID(ID),
mCoord(position),
mSpeed(),
mAbilityTime(sf::seconds(5)),
mSoundHandler(soundhandler),
mAnimationhandler(64, 64, &mSprite),
mPlayerIndex(player),
canPushCrate(true){

	if (mID == 1){
		mSpeed = 2;
	}
	if (mID == 2){
		mSpeed = 2;
		canPushCrate = false;
	}
	if (mID == 3){

	}
	if (mID == 4){

	}
	mSprite.setTexture(*texture, true);
	mSprite.setTextureRect(sf::IntRect(1*64, 1*64, 64, 64));
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
int Cat::getPlayerIndex(){
	return mPlayerIndex;
}
void Cat::Update(float dt){
	if (!canMove) {
		if (interactionClock.getElapsedTime().asSeconds() > interactionTime.asSeconds()) {
			canMove = true;
		}
	}

	if (mMoving){
		if (direction == 4 && mPosition.y != newPos.y) {
			mPosition.y -= (1 * mSpeed);
			if (mDashing == true){
				mAnimationhandler.animation(4, 5, sf::milliseconds(250));
			}
			else
				mAnimationhandler.animation(1, 5, sf::milliseconds(50));
		}
		else if (direction == 3 && mPosition.y != newPos.y) {
			mPosition.y += (1 * mSpeed);
			if (mDashing == true){
				mAnimationhandler.animation(5, 5, sf::milliseconds(250));
			}
			else
				mAnimationhandler.animation(0, 5, sf::milliseconds(50));
		}
		else if (direction == 2 && mPosition.x != newPos.x) {
			mPosition.x -= (1 * mSpeed);
			if (mDashing == true){
				mAnimationhandler.animation(7, 5, sf::milliseconds(250));
			}
			else
				mAnimationhandler.animation(3, 5, sf::milliseconds(50));
			
		}
		else if (direction == 1 && mPosition.x != newPos.x) {
			mPosition.x += (1 * mSpeed);
			if (mDashing == true){
				mAnimationhandler.animation(6, 5, sf::milliseconds(250));
			}
			else
				mAnimationhandler.animation(2, 5, sf::milliseconds(50));
		}
		else {
			mMoving = false;
			
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
			mAnimationhandler.reset(direction);
		}
	}
	else
	{
		if (direction == 4) {
			mAnimationhandler.setFrame(1, 4);
		}
		if (direction == 3) {
			mAnimationhandler.setFrame(0, 0);
		}
		if (direction == 2) {
			mAnimationhandler.setFrame(3, 0);
		}
		if (direction == 1) {
			mAnimationhandler.setFrame(2, 0);
		}
	}
}

void Cat::moveForward(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving && canMove) {
		direction = 4;
		if (mGrid.isTilePassable(this, gridvector(mCoord.x, mCoord.y - 1), tileLayer, Entities)){
			newPos.y = mPosition.y - 64;
			mSoundHandler->PlaySound(1);
			mMoving = true;
		}
	}
}
void Cat::moveBackWards(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving && canMove) {
		direction = 3;
		if (mGrid.isTilePassable(this, gridvector(mCoord.x, mCoord.y + 1), tileLayer, Entities)){
			newPos.y = mPosition.y + 64;
			mMoving = true;
		}
	}
}
void Cat::moveLeft(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving && canMove) {
		direction = 2;
		if (mGrid.isTilePassable(this, gridvector(mCoord.x - 1, mCoord.y), tileLayer, Entities)){
			newPos.x = mPosition.x - 64;
			mMoving = true;
		}
	}
}
void Cat::moveRight(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving && canMove) {
		direction = 1;
		if (mGrid.isTilePassable(this, gridvector(mCoord.x + 1, mCoord.y), tileLayer, Entities)){
			newPos.x = mPosition.x + 64;
			mMoving = true;
			
		}
	}
}

void Cat::useAbility(TileLayer *tileLayer, std::vector<Entity*> *Entities){
	//Shadow
	if (mID == 1)
	{
		shadowDash(tileLayer,Entities, direction);
	}
}

bool Cat::isInteracting(){
	return mInteracting;
}
bool Cat::isSolid(){
	return true;
}

void Cat::interaction(Usable *usable) {
	if (isInteracting()) {
		if (Computer *comp = dynamic_cast<Computer*>(usable)) {
			//playhackanimation
			comp->playSound();
			canMove = false;
			interactionClock.restart();
			interactionTime = sf::seconds(3);
			comp->Activate(sf::seconds(3));
		}
		if (Button *butt = dynamic_cast<Button*>(usable)) {

		}
	}
}
void Cat::CompleteInteraction(GameObject *object) {
	
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

void Cat::shadowDash(TileLayer *tileLayer, std::vector<Entity*> *Entities, int direc){
	int positiveNegative = 0;
	int position = 0;
	int positionY = 0;
	int positionX = 0;
//	int newPosition = 0;
//	int newCoord = 0;
	std::cout << "DASH!" << std::endl;
	if (mAbilityClock.getElapsedTime()>=mAbilityTime && !mMoving){
		if (direc == 1) {
			positiveNegative = 1;
			positionX = 1;
		}
		if (direc == 2) {
			positiveNegative = -1;
			positionX = -1;
		}
		if (direc == 3) {
			positiveNegative = 1;
			positionY = 1;
		}
		if (direc == 4) {
			positiveNegative = -1;
			positionY = -1;
		}
		/*if (direc == 1 || direc == 3) {
			positiveNegative = 1;
		}
		else {
			positiveNegative = -1;
		}

		if (direc == 1 || direc == 2) {
			position = mPosition.x;
		}
		else {
			position = mPosition.y;
		}*/

		std::cout << positionX << std::endl;
		std::cout << positionY << std::endl;
		if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities))) {
			cout << "1st tile is passable" << endl;
		}
		if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX*2), mCoord.y + (positionY*2)), tileLayer, Entities))) {
			cout << "2st tile is passable" << endl;
		}
		if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX*3), mCoord.y + (positionY*3)), tileLayer, Entities))) {
			cout << "3st tile is passable" << endl;
		}	
		if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX*4), mCoord.y + (positionY*4)), tileLayer, Entities))) {
			cout << "4st tile is passable" << endl;
		}
		if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX*2), mCoord.y + (positionY*2)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX*3), mCoord.y + (positionY*3)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX*4), mCoord.y + (positionY*4)), tileLayer, Entities))) {
			std::cout << "4 Tile dash" << std::endl;
			mSpeed = mSpeed * 4;
			position += (256 * positiveNegative);
			positiveNegative *= 3;
		//	newPos.x = mPosition.x + (256 * positiveNegative);
		//	mCoord.x + positiveNegative;
			mDashing = true;
			mMoving = true;
			mAbilityClock.restart();
			mSoundHandler->PlaySound(2);
		}
		else if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX*2), mCoord.y + (positionY*2)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX*3), mCoord.y + (positionY*3)), tileLayer, Entities))) {
			std::cout << "3 Tile dash" << std::endl;
			mSpeed = mSpeed * 4;
			position += (192 * positiveNegative);
			positiveNegative *= 2;
		//	newPos.x = mPosition.x + (192 * positiveNegative);
		//	mCoord.x + positiveNegative;
			mDashing = true;
			mMoving = true;
			mAbilityClock.restart();
		}
		else if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX*2), mCoord.y + (positionY*2)), tileLayer, Entities))) {
			std::cout << "2 Tile dash" << std::endl;
			mSpeed = mSpeed * 4;
			position += (128 * positiveNegative);
			positiveNegative *= 1;
		//	newPos.x = mPosition.x + (128 * positiveNegative);
		//	mCoord.x + positiveNegative;
			mDashing = true;
			mMoving = true;
			mAbilityClock.restart();
		}
		else {
			positiveNegative = 0;
		}
		/*else if ((mGrid.isTilePassable(mCoord, gridvector(mCoord.x + (positionX), mCoord.y +(positionY)), tileLayer, Entities))) {
			mSpeed = mSpeed * 4;
			position += (64 * positiveNegative);
		//	newPos.x = mPosition.x + (64 * positiveNegative);
		//	mCoord.x + positiveNegative;
			mDashing = true;
			mMoving = true;
			mAbilityClock.restart();
		}*/
	/*	if (direction == 1 && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x + 1, mCoord.y), tileLayer, Entities)) && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x + 2, mCoord.y), tileLayer, Entities))){
			mSpeed = mSpeed * 4;
			newPos.x = mPosition.x + 128;
			mCoord.x++;
			mDashing = true;
			mMoving = true;
			mAbilityClock.restart();
		}
		if (direction == 2 && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x - 1, mCoord.y), tileLayer, Entities)) && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x - 2, mCoord.y), tileLayer, Entities))){
			mSpeed = mSpeed * 4;
			newPos.x = mPosition.x - 128;
			mCoord.x--;
			mDashing = true;
			mMoving = true;
			mAbilityClock.restart();
		}
		if (direction == 3 && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x, mCoord.y + 1), tileLayer, Entities)) && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x, mCoord.y + 2), tileLayer, Entities))){
			mSpeed = mSpeed * 4;
			newPos.y = mPosition.y + 128;
			mCoord.y++;
			mDashing = true;
			mMoving = true;
			mAbilityClock.restart();
		}
		if (direction == 4 && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x, mCoord.y - 1), tileLayer, Entities)) && (mGrid.isTilePassable(mCoord, gridvector(mCoord.x, mCoord.y - 2), tileLayer, Entities))){
			mSpeed = mSpeed * 4;
			newPos.y = mPosition.y - 128;
			mCoord.y--;
			mDashing = true;
			mMoving = true;
			mAbilityClock.restart();
		}
		*/
		std::cout << position << std::endl;
		std::cout << positiveNegative << std::endl;
		if (direc == 1 || direc == 2) {
			newPos.x = mPosition.x + position;
			mCoord.x += positiveNegative;
		}
		else {
			newPos.y = mPosition.y + position;
			mCoord.y += positiveNegative;
		}
	}

}

bool Cat::getDashing(){
	return mDashing;
}

// SNOW \\

bool Cat::snowHax(){
	if (mID == 2){
		
		return true;
	}
	else
		return false;
}
Layer Cat::getLayer() {
	return FRONT;
}