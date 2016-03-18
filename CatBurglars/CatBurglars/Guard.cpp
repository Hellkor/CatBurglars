#include "Guard.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
string DIRECTORY = "Resources/AI/";

Guard::Guard(TextureHandler *textures, gridvector position, int ID,string AIscript, SoundHandler *soundhandler , string directory,string leveltype,int guardtype) : GameObject(),
mID(ID),
mCoords(position),
mSpeed(1),
mAIfile(AIscript),
mAnimationhandler(64, 128, &mSprite),
mSoundHandler(soundhandler),
mRange(3),
mDirectory(directory){

	if (guardtype == 1) {
		mGuardType = Normal;
		mSpeed = 1;
	}
	if (guardtype == 2) {
		mGuardType = Douglas;
		mSpeed = 0.5;
	}
	if (leveltype == "Prison1") {
		if (mGuardType == Normal) {
			mSprite.setTexture(*textures->GetTexture(5), true);
		}
		if (mGuardType == Douglas) {
			mSprite.setTexture(*textures->GetTexture(7), true);
		}
		
	}
	if (leveltype == "Museum") {
		if (mGuardType == Normal) {
			mSprite.setTexture(*textures->GetTexture(6), true);
		}
		if (mGuardType == Douglas) {
			mSprite.setTexture(*textures->GetTexture(7), true);
		}
		
	}
	
	mSprite.setTextureRect(sf::IntRect(1 * 64, 3 * 128, 64, 128));
	
	
	//Starting position
	mPosition = sf::Vector2i(mCoords.x * 64, mCoords.y * 64);
	//Starting Command
	mCurrentCommand.xPos = mCoords.x;
	mCurrentCommand.yPos = mCoords.y;
	mCurrentCommand.direction = "E";

	loadAI(mAIfile);
	
	

	mHitboxSprite.setTexture(*textures->GetTexture(99));
	mHitboxSprite.setPosition((sf::Vector2f)mPosition);
	
	//setVision("E",0,0);

	mWalkSound.setBuffer(*mSoundHandler->getSound(1));

}
GuardType Guard::getGuardType() {
	return mGuardType;
}
void Guard::setVision(string face, TileLayer *tiles, std::vector<Entity*> *entities) {
	while (!mVision.empty()) {
		delete mVision.back();
		mVision.pop_back();
	}
	mVision.clear();
	int range = mRange;
	width = 1;
	int height = 0;
	mFace = face;
	bool rightVision = true;
	bool leftVision = true;
	bool forwardVision = true;
	if (mFace == "N") {
		mSprite.setTextureRect(sf::IntRect(0 * 64, 3 * 128, 64, 128));

		for (int i = 0; i <= range; i++) {
			if (mGrid.isLightPassable(this, gridvector(mCoords.x, mCoords.y - i), tiles, entities)&& forwardVision) {
				mVision.push_back(new gridvector(mCoords.x, mCoords.y - i));
			}
			else
				forwardVision = false;
			rightVision = true;
			leftVision = true;
			for (int j = 1; j < width; j++) {
				if (mGrid.isLightPassable(this, gridvector(mCoords.x + j, mCoords.y - i), tiles, entities)&& rightVision && forwardVision) {
					mVision.push_back(new gridvector(mCoords.x + j, mCoords.y - i));
				}
				else
					rightVision = false;
				if (mGrid.isLightPassable(this, gridvector(mCoords.x + -j, mCoords.y - i), tiles, entities)&& leftVision && forwardVision) {
					mVision.push_back(new gridvector(mCoords.x + -j, mCoords.y - i));
				}
				else
					leftVision = false;
				}
			width = 2;
		}
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
	}
	if (mFace == "S") {
		mSprite.setTextureRect(sf::IntRect(0 * 64, 2 * 128, 64, 128));
		for (int i = 0; i <= range; i++) {
			if (mGrid.isLightPassable(this, gridvector(mCoords.x, mCoords.y + i), tiles, entities) && forwardVision) {
				mVision.push_back(new gridvector(mCoords.x, mCoords.y + i));
			}
			else
				forwardVision = false;
			rightVision = true;
			leftVision = true;
			for (int j = 1; j < width; j++) {
					if (mGrid.isLightPassable(this, gridvector(mCoords.x + j, mCoords.y + i), tiles, entities) && rightVision && forwardVision) {
						mVision.push_back(new gridvector(mCoords.x + j, mCoords.y + i));
					}
					else
						rightVision = false;
					if (mGrid.isLightPassable(this, gridvector(mCoords.x + -j, mCoords.y + i), tiles, entities) && leftVision && forwardVision) {
						mVision.push_back(new gridvector(mCoords.x + -j, mCoords.y + i));
					}
					else
						leftVision = false;
				}
			width = 2;

		}
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);

	}
	if (mFace == "E") {
		mSprite.setTextureRect(sf::IntRect(0 * 64, 0 * 128, 64, 128));
		for (int i = 0; i <= range; i++) {
			if (mGrid.isLightPassable(this, gridvector(mCoords.x + i, mCoords.y), tiles, entities) && forwardVision) {
				mVision.push_back(new gridvector(mCoords.x + i, mCoords.y));
			}
			else
				forwardVision = false;
			rightVision = true;
			leftVision = true;
			for (int j = 1; j < width; j++) {
				if (mGrid.isLightPassable(this, gridvector(mCoords.x + i, mCoords.y + j), tiles, entities) && rightVision && forwardVision) {
					mVision.push_back(new gridvector(mCoords.x + i, mCoords.y + j));
				}
				else
					rightVision = false;
				if (mGrid.isLightPassable(this, gridvector(mCoords.x + i, mCoords.y - j), tiles, entities) && leftVision && forwardVision) {
					mVision.push_back(new gridvector(mCoords.x + i, mCoords.y - j));
				}
				else
					leftVision = false;
			}
			width = 2;
		}

		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
	}
	if (mFace == "W") {
		mSprite.setTextureRect(sf::IntRect(0 * 64, 1 * 128, 64, 128));
		for (int i = 0; i <= range; i++) {
			if (mGrid.isLightPassable(this, gridvector(mCoords.x - i, mCoords.y), tiles, entities) && forwardVision) {
				mVision.push_back(new gridvector(mCoords.x - i, mCoords.y));
			}
			else
				forwardVision = false;
			rightVision = true;
			leftVision = true;
			for (int j = 1; j < width; j++) {
				if (mGrid.isLightPassable(this, gridvector(mCoords.x - i, mCoords.y + j), tiles, entities) && rightVision && forwardVision) {
					mVision.push_back(new gridvector(mCoords.x - i, mCoords.y + j));
				}
				else
					rightVision = false;
				if (mGrid.isLightPassable(this, gridvector(mCoords.x - i, mCoords.y - j), tiles, entities) && leftVision && forwardVision) {
					mVision.push_back(new gridvector(mCoords.x - i, mCoords.y - j));
				}
				else
					leftVision = false;
			}
			width = 2;
		}
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
	}
	
}
void Guard::UpdateConePos() {
	int range = mRange;
	

	if (mFace == "N") {
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
	}
	if (mFace == "S") {
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
	}
	if (mFace == "E") {
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
	}
	if (mFace == "W") {
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
	}
}
Guard::~Guard(){
	while (!mVision.empty()) {
		delete mVision.back();
		mVision.pop_back();
	}
}
//Render sprite on screen
void Guard::Render(sf::RenderWindow *mainWindow){

	mHitboxSprite.setPosition((sf::Vector2f)mPosition);
	mSprite.setPosition(sf::Vector2f(mPosition.x,mPosition.y-64));

	for each (gridvector *v in mVision) {
		mHitboxSprite.setPosition(v->x * 64, v->y * 64);
		mainWindow->draw(mHitboxSprite);
	}

	mainWindow->draw(mSprite);




	
}
void Guard::loadAI(string filename){
	mCommandQueue.clear();

	cout << "trying to load" << endl;
	ifstream inputFile("Maps/" + mDirectory + "/AI/" + filename + ".txt");
	string input;

	while (!inputFile.eof())
	{
		Command command;
		inputFile >> input;
		for (std::string::size_type i = 0; i < input.size(); i++)
		{
			char *c = &input[i];
			*c = toupper(*c);
		}
		if (input != "WAIT")
		{
			command.xPos = stoi(input);
			inputFile >> input;
			command.yPos = stoi(input);
			inputFile >> input;
			for (std::string::size_type i = 0; i < input.size(); i++)
			{
				char *c = &input[i];
				*c = toupper(*c);
			}
		}
		command.direction = input;
		command.temporary = false;

		mCommandQueue.push_back(command);
	}
	
	
}
void Guard::AImovement(TileLayer *tiles, std::vector<Entity*> *entities, Pathfinder *pathfinder){

	mPathfinder = pathfinder;

	if (!mMoving && mClock.getElapsedTime() >= sf::seconds(1) && mQueuePos < mCommandQueue.size())
	{
		if (mCommandQueue[mQueuePos].direction != "WAIT")
		{
			gridvector startNode, targetNode;
			startNode = mCoords;
			targetNode = gridvector(mCommandQueue[mQueuePos].xPos, mCommandQueue[mQueuePos].yPos);
			vector<PathNode*> path = pathfinder->FindPath(startNode, targetNode);

			if (path.size() > 1)
			{
				if (path[1]->GetGridPosition().x < mCoords.x)
					moveLeft(tiles, entities);
				else if (path[1]->GetGridPosition().x > mCoords.x)
					moveRight(tiles, entities);
				else if (path[1]->GetGridPosition().y < mCoords.y)
					moveForward(tiles, entities);
				else if (path[1]->GetGridPosition().y > mCoords.y)
					moveBackWards(tiles, entities);
			}
			else
			{
				setVision(mCommandQueue[mQueuePos].direction, tiles, entities);
				if (mCommandQueue[mQueuePos].temporary)
					mCommandQueue.erase(mCommandQueue.begin() + mQueuePos);
				else
					mQueuePos += 1;
				if (mQueuePos >= mCommandQueue.size())
					mQueuePos = 0;
			}
		}
		else
		{
			mClock.restart();
			if (mCommandQueue[mQueuePos].temporary)
				mCommandQueue.erase(mCommandQueue.begin() + mQueuePos);
			else
				mQueuePos += 1;
			if (mQueuePos >= mCommandQueue.size())
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
			mWalkSound.stop();
			// säkrar att den håller rätt position
			if (direction == 4) {
				mCoords.y--;
			//	setVision("N", tiles, entities);
				if (mPosition.y != newPos.y)
					mPosition.y = newPos.y;

			}
			if (direction == 3) {
				mCoords.y++;
			//	setVision("S", tiles, entities);
				if (mPosition.y != newPos.y)
					mPosition.y = newPos.y;
			}
			if (direction == 2) {
				mCoords.x--;
			//	setVision("W", tiles, entities);
				if (mPosition.x != newPos.x)
					mPosition.x = newPos.x;
			}
			if (direction == 1) {
				mCoords.x++;
			//	setVision("E", tiles, entities);
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
		if (mGrid.isTilePassable(this, gridvector(mCoords.x, mCoords.y - 1), tileLayer, Entities)){
			newPos.y = mPosition.y - 64;
			setVision("N", tileLayer, Entities);
			mMoving = true;
		}
	}
}
void Guard::moveBackWards(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 3;
		if (mGrid.isTilePassable(this, gridvector(mCoords.x, mCoords.y + 1), tileLayer, Entities)){
			newPos.y = mPosition.y + 64;
			setVision("S", tileLayer, Entities);
			mMoving = true;
		}
	}
}
void Guard::moveLeft(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 2;
		if (mGrid.isTilePassable(this, gridvector(mCoords.x - 1, mCoords.y), tileLayer, Entities)){
			newPos.x = mPosition.x - 64;
			setVision("W", tileLayer, Entities);
			mMoving = true;
		}
	}
}
void Guard::moveRight(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving) {
		direction = 1;
		if (mGrid.isTilePassable(this, gridvector(mCoords.x + 1, mCoords.y), tileLayer, Entities)){
			newPos.x = mPosition.x + 64;
			setVision("E", tileLayer, Entities);
			mMoving = true;

		}
	}
}
void Guard::interaction(Usable *usable) {

	if (Button *butt = dynamic_cast<Button*>(usable)) {
		if (mCoords == butt->getCoords()) {
			butt->Activate(sf::seconds(0));
		}
	}

}

void Guard::SetDistraction(gridvector pos, int distractSeconds, int direc)
{
	Command distractionCommand;
	int X = pos.x;
	int Y = pos.y;
	string facing ="N";
	if (direc == 1) {
		cout << "Setting position + X" << endl;
		X++;
		facing = "W";
	}
	else if (direc == 2) {
		cout << "Setting position - X" << endl;
		X--;
		facing = "E";
	}
	else if (direc == 3) {
		cout << "Setting position + Y" << endl;
		Y++;
		facing = "N";
	}
	else if (direc == 4) {
		cout << "Setting position - Y" << endl;
		Y--;
		facing = "S";
	}
	distractionCommand.xPos = X;
	distractionCommand.yPos = Y;
	if (direc > 0) {
		distractionCommand.direction = facing; // for now
	}
	else {
		cout << "Faceing the way I am standing "<< direction <<endl;
		distractionCommand.direction = mFace;
	}
	distractionCommand.temporary = true;
	if (mCommandQueue[mQueuePos].temporary == true)
		mCommandQueue.erase(mCommandQueue.begin() + mQueuePos);
	for (int i = 0; i < distractSeconds; i++)
	{
		Command distractWaitCommand;
		distractWaitCommand.direction = "WAIT";
		distractWaitCommand.temporary = true;
		mCommandQueue.insert(mCommandQueue.begin() + mQueuePos, distractWaitCommand);
	}
	mCommandQueue.insert(mCommandQueue.begin() + mQueuePos, distractionCommand);
}

void Guard::RemoveTemporaryWaits()
{
	for (std::vector<Command>::size_type i = 0; i < mCommandQueue.size(); i++)
	{
		if (mCommandQueue[i].direction == "WAIT" && mCommandQueue[i].temporary)
		{
			mCommandQueue.erase(mCommandQueue.begin() + i);
			i--;
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
	return false;
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