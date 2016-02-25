#include "Guard.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
string DIRECTORY = "Resources/AI/";

Guard::Guard(TextureHandler *textures, gridvector position, int ID,string AIscript, SoundHandler *soundhandler) : GameObject(),
mID(ID),
mCoords(position),
mSpeed(1),
mAIfile(AIscript),
mAnimationhandler(64, 128, &mSprite),
mSoundHandler(soundhandler),
mRange(3){
	mSprite.setTexture(*textures->GetTexture(5), true);
	mSprite.setTextureRect(sf::IntRect(1*64, 3*128, 64, 128));
	//Starting position
	mPosition = sf::Vector2i(mCoords.x * 64, mCoords.y * 64);

	loadAI(mAIfile);
	

	mConvex.setPointCount(3);
	mConvex.setTexture(textures->GetTexture(99));

	mHitboxSprite.setTexture(*textures->GetTexture(99));
	mHitboxSprite.setPosition((sf::Vector2f)mPosition);
	
	setVision("E");

	mWalkSound.setBuffer(*mSoundHandler->getSound(1));

}
void Guard::setVision(string face) {
	mVision.clear();
	int range = mRange;
	width = 1;
	int height = 0;
	mFace = face;

	if (mFace == "N") {
		mSprite.setTextureRect(sf::IntRect(0 * 64, 3 * 128, 64, 128));

		for (int i = 0; i <= range; i++) {
			mVision.push_back(new gridvector(mCoords.x, mCoords.y - i));

			for (int j = 1; j < width; j++) {
				mVision.push_back(new gridvector(mCoords.x + j, mCoords.y - i));
				mVision.push_back(new gridvector(mCoords.x + -j, mCoords.y - i));
			}

			width++;
		}
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
		// define the points
		mConvex.setPoint(0, sf::Vector2f(conePos.x, conePos.y));
		mConvex.setPoint(1, sf::Vector2f(conePos.x - 32 - (width - 2) * 64, conePos.y - 32 - range * 64));
		mConvex.setPoint(2, sf::Vector2f(conePos.x + 32 + (width - 2) * 64, conePos.y - 32 - range * 64));
	}
	if (mFace == "S") {
		mSprite.setTextureRect(sf::IntRect(0 * 64, 2 * 128, 64, 128));
		for (int i = 0; i <= range; i++) {

			mVision.push_back(new gridvector(mCoords.x, mCoords.y + i));

			for (int j = 1; j < width; j++) {
				mVision.push_back(new gridvector(mCoords.x + j, mCoords.y + i));
				mVision.push_back(new gridvector(mCoords.x + -j, mCoords.y + i));
			}

			width++;

		}
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
		// define the points
		mConvex.setPoint(0, sf::Vector2f(conePos.x, conePos.y));
		mConvex.setPoint(1, sf::Vector2f(conePos.x - 32 - (width - 2) * 64, conePos.y + 32 + range * 64));
		mConvex.setPoint(2, sf::Vector2f(conePos.x + 32 + (width - 2) * 64, conePos.y + 32 + range * 64));

	}
	if (mFace == "E") {
		mSprite.setTextureRect(sf::IntRect(0 * 64, 0 * 128, 64, 128));
		for (int i = 0; i <= range; i++) {

			mVision.push_back(new gridvector(mCoords.x + i, mCoords.y));

			for (int j = 1; j < width; j++) {
				mVision.push_back(new gridvector(mCoords.x + i, mCoords.y + j));
				mVision.push_back(new gridvector(mCoords.x + i, mCoords.y - j));
			}

			width++;
		}

		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
		// define the points
		mConvex.setPoint(0, sf::Vector2f(conePos.x, conePos.y));
		mConvex.setPoint(1, sf::Vector2f(conePos.x + 32 + range * 64, conePos.y - 32 - (width - 2) * 64));
		mConvex.setPoint(2, sf::Vector2f(conePos.x + 32 + range * 64, conePos.y + 32 + (width - 2) * 64));
	}
	if (mFace == "W") {
		mSprite.setTextureRect(sf::IntRect(0 * 64, 1 * 128, 64, 128));
		for (int i = 0; i <= range; i++) {

			mVision.push_back(new gridvector(mCoords.x - i, mCoords.y));

			for (int j = 1; j < width; j++) {
				mVision.push_back(new gridvector(mCoords.x - i, mCoords.y + j));
				mVision.push_back(new gridvector(mCoords.x - i, mCoords.y - j));
			}

			width++;
		}
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
		// define the points
		mConvex.setPoint(0, sf::Vector2f(conePos.x, conePos.y));
		mConvex.setPoint(1, sf::Vector2f(conePos.x - 32 - range * 64, conePos.y + 32 + (width - 2) * 64));
		mConvex.setPoint(2, sf::Vector2f(conePos.x - 32 - range * 64, conePos.y - 32 - (width - 2) * 64));
	}
}
void Guard::UpdateConePos() {
	int range = mRange;
	

	if (mFace == "N") {
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
		// define the points
		mConvex.setPoint(0, sf::Vector2f(conePos.x, conePos.y));
		mConvex.setPoint(1, sf::Vector2f(conePos.x - 32 - (width - 2) * 64, conePos.y - 32 - range * 64));
		mConvex.setPoint(2, sf::Vector2f(conePos.x + 32 + (width - 2) * 64, conePos.y - 32 - range * 64));
	}
	if (mFace == "S") {
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
		// define the points
		mConvex.setPoint(0, sf::Vector2f(conePos.x, conePos.y));
		mConvex.setPoint(1, sf::Vector2f(conePos.x - 32 - (width - 2) * 64, conePos.y + 32 + range * 64));
		mConvex.setPoint(2, sf::Vector2f(conePos.x + 32 + (width - 2) * 64, conePos.y + 32 + range * 64));
	}
	if (mFace == "E") {
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
		// define the points
		mConvex.setPoint(0, sf::Vector2f(conePos.x, conePos.y));
		mConvex.setPoint(1, sf::Vector2f(conePos.x + 32 + range * 64, conePos.y - 32 - (width - 2) * 64));
		mConvex.setPoint(2, sf::Vector2f(conePos.x + 32 + range * 64, conePos.y + 32 + (width - 2) * 64));
	}
	if (mFace == "W") {
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
		// define the points
		mConvex.setPoint(0, sf::Vector2f(conePos.x, conePos.y));
		mConvex.setPoint(1, sf::Vector2f(conePos.x - 32 - range * 64, conePos.y + 32 + (width - 2) * 64));
		mConvex.setPoint(2, sf::Vector2f(conePos.x - 32 - range * 64, conePos.y - 32 - (width - 2) * 64));
	}
}
Guard::~Guard(){

}
//Render sprite on screen
void Guard::Render(sf::RenderWindow *mainWindow){

	mHitboxSprite.setPosition((sf::Vector2f)mPosition);
	mSprite.setPosition(sf::Vector2f(mPosition.x,mPosition.y-64));
	mainWindow->draw(mSprite);


	mainWindow->draw(mConvex);

	for each (gridvector *v in mVision) {
		mHitboxSprite.setPosition(v->x * 64, v->y * 64);
		//mainWindow->draw(mHitboxSprite);
	}
}
void Guard::loadAI(string filename){
	mCommandQueue.clear();

	ifstream inputFile("Resources/AI/" + filename + ".txt");
	string input;

	while (!inputFile.eof()){
		inputFile >> input;
		
		string tempinput;
		for (std::string::size_type i = 0; i < input.size(); i++) {
			char *c = &input[i];
			*c = toupper(*c);
		}
		
		mCommandQueue.push_back(input);
	}
	

}
void Guard::AImovement(TileLayer *tiles, std::vector<Entity*> *entities){

	

	if (!mMoving && mClock.getElapsedTime() >= sf::seconds(1) && mQueuePos < mCommandQueue.size()){


		if (mCommandQueue[mQueuePos] == "N" ){
			moveForward(tiles, entities);
		}
		if (mCommandQueue[mQueuePos] == "S" ){
			moveBackWards(tiles, entities);
		}
		if (mCommandQueue[mQueuePos] == "W" ){
			moveLeft(tiles, entities);
		}
		if (mCommandQueue[mQueuePos] == "E" ){
			moveRight(tiles, entities);
		}
		if (mCommandQueue[mQueuePos] == "TN") {
			setVision("N");
		}
		if (mCommandQueue[mQueuePos] == "TS") {
			setVision("S");
		}
		if (mCommandQueue[mQueuePos] == "TW") {
			setVision("W");
		}
		if (mCommandQueue[mQueuePos] == "TE") {
			setVision("E");
		}
		if (mCommandQueue[mQueuePos] == "wait"){
			mClock.restart();
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
	UpdateConePos();
	if (mWalkSound.getStatus() == sf::Sound::Playing) {
		mWalkSound.setVolume(mSoundHandler->distanceSound(this));
	}
	if (mMoving){
		if (!(mWalkSound.getStatus() == sf::Sound::Playing)) {
			mWalkSound.play();
		}
		if (direction == 4 && mPosition.y != newPos.y) {
			mPosition.y -= (1 * mSpeed);
			mAnimationhandler.animation(3, 5, sf::milliseconds(150));
		}
		else if (direction == 3 && mPosition.y != newPos.y) {
			mPosition.y += (1 * mSpeed);
			mAnimationhandler.animation(2, 5, sf::milliseconds(150));
		}
		else if (direction == 2 && mPosition.x != newPos.x) {
			mPosition.x -= (1 * mSpeed);
			mAnimationhandler.animation(1, 5, sf::milliseconds(200));
		}
		else if (direction == 1 && mPosition.x != newPos.x) {
			mPosition.x += (1 * mSpeed);
			mAnimationhandler.animation(0, 5, sf::milliseconds(200));
		}
		else {
			mMoving = false;

			// säkrar att den håller rätt position
			if (direction == 4) {
				mCoords.y--;
				setVision("N");
				if (mPosition.y != newPos.y)
					mPosition.y = newPos.y;

			}
			if (direction == 3) {
				mCoords.y++;
				setVision("S");
				if (mPosition.y != newPos.y)
					mPosition.y = newPos.y;
			}
			if (direction == 2) {
				mCoords.x--;
				setVision("W");
				if (mPosition.x != newPos.x)
					mPosition.x = newPos.x;
			}
			if (direction == 1) {
				mCoords.x++;
				setVision("E");
				if (mPosition.x != newPos.x)
					mPosition.x = newPos.x;
			}
			//mAnimationhandler.reset(direction);
		}
	}
}

void Guard::moveForward(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 4;
		if (mGrid.isTilePassable(mCoords, gridvector(mCoords.x, mCoords.y - 1), tileLayer, Entities)){
			newPos.y = mPosition.y - 64;
			setVision("N");
			mMoving = true;
		}
	}
}
void Guard::moveBackWards(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 3;
		if (mGrid.isTilePassable(mCoords, gridvector(mCoords.x, mCoords.y + 1), tileLayer, Entities)){
			newPos.y = mPosition.y + 64;
			setVision("S");
			mMoving = true;
		}
	}
}
void Guard::moveLeft(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 2;
		if (mGrid.isTilePassable(mCoords, gridvector(mCoords.x - 1, mCoords.y), tileLayer, Entities)){
			newPos.x = mPosition.x - 64;
			setVision("W");
			mMoving = true;
		}
	}
}
void Guard::moveRight(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 1;
		if (mGrid.isTilePassable(mCoords, gridvector(mCoords.x + 1, mCoords.y), tileLayer, Entities)){
			newPos.x = mPosition.x + 64;
			setVision("E");
			mMoving = true;

		}
	}
}
bool Guard::getIntersection(GameObject *obj) {
	for each (gridvector *v in mVision) {
		if (obj->getCoords() == v) {
				return true;
		}
	}
	return false;
}
bool Guard::isInteracting(){
	return mInteracting;
}
bool Guard::isSolid(){
	return true;
}

//Returns position of sprite
sf::Vector2i Guard::GetPosition(){
	return mPosition;
}
gridvector Guard::getCoords(){
	return mCoords;
}

int Guard::getDirection(){
	return direction;
}

bool Guard::isMoving(){
	return mMoving;
}
Layer Guard::getLayer() {
	return FRONT;
}