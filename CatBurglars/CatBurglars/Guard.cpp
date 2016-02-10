#include "Guard.h"
#include <iostream>
#include <fstream>

string DIRECTORY = "Resources/AI/";

Guard::Guard(sf::Texture *texture, gridvector position, int ID,string AIscript) : GameObject(),
mID(ID),
mCoord(position),
mSpeed(1),
mAIfile(AIscript){
	mSprite.setTexture(*texture, true);
	//Starting position
	mPosition = sf::Vector2i(mCoord.x * 64, mCoord.y * 64);

	loadAI(mAIfile);
}
Guard::~Guard(){

}
//Render sprite on screen
void Guard::Render(sf::RenderWindow *mainWindow){


	mSprite.setPosition((sf::Vector2f)mPosition);
	mainWindow->draw(mSprite);
}
void Guard::loadAI(string filename){
	mCommandQueue.clear();

	ifstream inputFile("Resources/AI/" + filename + ".txt");
	string input;

	while (!inputFile.eof()){
		inputFile >> input;
		mCommandQueue.push_back(input);
	}
	

}
void Guard::AImovement(TileLayer *tiles, std::vector<Entity*> *entities){

	

	if (!mMoving && mWait <= 0 && mQueuePos < mCommandQueue.size()){


		if (mCommandQueue[mQueuePos] == "forward"){
			moveForward(tiles, entities);
		}
		if (mCommandQueue[mQueuePos] == "backwards"){
			moveBackWards(tiles, entities);
		}
		if (mCommandQueue[mQueuePos] == "left"){
			moveLeft(tiles, entities);
		}
		if (mCommandQueue[mQueuePos] == "right"){
			moveRight(tiles, entities);
		}
		if (mCommandQueue[mQueuePos] == "wait"){
			mWait = 100;//stoi(mCommandQueue[mQueuePos + 1]);
		}

		
		
		if (mQueuePos <= mCommandQueue.size()){
			mQueuePos += 1;
		}
		if (mQueuePos > mCommandQueue.size() - 1){
			mQueuePos = 0;
		}
	}



}
void Guard::Update(float dt){

	mWait -= dt;

	if (mMoving){
		if (direction == 4 && mPosition.y != newPos.y) {
			mPosition.y -= (1 * mSpeed);
		}
		else if (direction == 3 && mPosition.y != newPos.y) {
			mPosition.y += (1 * mSpeed);
		}
		else if (direction == 2 && mPosition.x != newPos.x) {
			mPosition.x -= (1 * mSpeed);

		}
		else if (direction == 1 && mPosition.x != newPos.x) {
			mPosition.x += (1 * mSpeed);
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
		}
	}
}

void Guard::moveForward(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 4;
		if (mGrid.isTilePassable(mCoord, gridvector(mCoord.x, mCoord.y - 1), tileLayer, Entities)){
			newPos.y = mPosition.y - 64;


			mMoving = true;
		}
	}
}
void Guard::moveBackWards(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 3;
		if (mGrid.isTilePassable(mCoord, gridvector(mCoord.x, mCoord.y + 1), tileLayer, Entities)){
			newPos.y = mPosition.y + 64;


			mMoving = true;
		}
	}
}
void Guard::moveLeft(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 2;
		if (mGrid.isTilePassable(mCoord, gridvector(mCoord.x - 1, mCoord.y), tileLayer, Entities)){
			newPos.x = mPosition.x - 64;


			mMoving = true;
		}
	}
}
void Guard::moveRight(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 1;
		if (mGrid.isTilePassable(mCoord, gridvector(mCoord.x + 1, mCoord.y), tileLayer, Entities)){
			newPos.x = mPosition.x + 64;


			mMoving = true;

		}
	}
}

bool Guard::isInteracting(){
	return mInteracting;
}
bool Guard::isSolid(){
	return false;
}

//Returns position of sprite
sf::Vector2i Guard::GetPosition(){
	return mPosition;
}

int Guard::getDirection(){
	return direction;
}

bool Guard::isMoving(){
	return mMoving;
}