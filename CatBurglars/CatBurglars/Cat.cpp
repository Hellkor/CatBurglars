#include "Cat.h"
#include <iostream>


int TILESIZE = 64;


Cat::Cat(TextureHandler *texturehandler, gridvector position, int ID, SoundHandler *soundhandler,int player) : GameObject(),
mID(ID),
mCoord(position),
mSpeed(),
mAbilityTime(),
mSoundHandler(soundhandler),
mAnimationhandler(64, 64, &mSprite),
mPlayerIndex(player),
canPushCrate(true){

	if (player == 1) {
		mSoundHandler->initializeCat1(this);
		//mID = 3;
	}
	if (player == 2) {
		mSoundHandler->initializeCat2(this);
		//mID = 4;
	}
	if (mID == 1){
		mSpeed = 2;
		mSprite.setTexture(*texturehandler->GetTexture(10), true);
		mAbilitySprite.setTexture(*texturehandler->GetTexture(50), true);
		mDashSound.setBuffer(*mSoundHandler->getSound(2));
		mAbilityTime = sf::seconds(5);
	}
	if (mID == 2){
		mSpeed = 2;
		mSprite.setTexture(*texturehandler->GetTexture(9), true);
		mAbilitySprite.setTexture(*texturehandler->GetTexture(50), true);
		canPushCrate = false;
	}
	if (mID == 3){
		mSpeed = 2;
		mSprite.setTexture(*texturehandler->GetTexture(16), true);
		canPushCrate = false;
		mAbilitySprite.setTexture(*texturehandler->GetTexture(50), true);
		mAbilityTime = sf::seconds(5);
	}
	if (mID == 4){
		mSpeed = 2;
		mThrowSprite.setTexture(*texturehandler->GetTexture(19), true);
		mThrowSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		mSprite.setTexture(*texturehandler->GetTexture(17), true);
		mAbilitySprite.setTexture(*texturehandler->GetTexture(50), true);
		mAbilityTime = sf::seconds(15);
		mRangeSprite.setTexture(*texturehandler->GetTexture(50));
	}
	
	mSprite.setTextureRect(sf::IntRect(1*64, 1*64, 64, 64));
	//Starting position
	mPosition = sf::Vector2i(mCoord.x * 64, mCoord.y * 64);

}
Cat::~Cat(){
	cout << "CAT !!!Deleted" << endl;
}

//Render sprite on screen
void Cat::Render(sf::RenderWindow *mainWindow){
	mSprite.setPosition((sf::Vector2f)mPosition);
	mainWindow->draw(mSprite);
	if (mObjectThrown) {
		mThrowSprite.setPosition((sf::Vector2f)ThrownPos);
		mThrowSprite.rotate(5);
		mainWindow->draw(mThrowSprite);
	}
	if (mScooterPrepare && ScooterRange != 0) {
		cout << "Render range" << endl;
		if (rangePos.x >= 0 && rangePos.y >= 0) {
		mRangeSprite.setPosition((sf::Vector2f)rangePos);
		}
			mainWindow->draw(mRangeSprite);
	}
}

void Cat::RenderGUI(sf::RenderWindow *mainWindow) {
	if (mPlayerIndex == 1) {
		mAbilitySprite.setPosition((mainWindow->getSize().x)*-0.2, (mainWindow->getSize().y)*0.8);
	}
	else {
		mAbilitySprite.setPosition((mainWindow->getSize().x)*0.7, (mainWindow->getSize().y)*0.8);
	}
	if (mCooldown) {
		mAbilitySprite.setTextureRect(sf::IntRect(64, 0, 64, 64));
	}
	else {
		mAbilitySprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	}
	mainWindow->draw(mAbilitySprite);
}

int Cat::getPlayerIndex(){
	return mPlayerIndex;
}

int Cat::getID() {
	return mID;
}


void Cat::Update(float dt){
	if (mID == 3) {
		if (!mSocksCooldown && !mSocksDistract && socksMoved) {
			mAbilityClock.restart();
			mSocksCooldown = true;
		}
		else if (mAbilityClock.getElapsedTime() >= mAbilityTime && mCooldown && mSocksCooldown) {
			mCooldown = false;
		}
	}
	else if(mAbilityClock.getElapsedTime() >= mAbilityTime && mCooldown) {

		mCooldown = false;
	}

	if (!canMove) {
		if (interactionClock.getElapsedTime().asSeconds() > interactionTime.asSeconds()) {
			canMove = true;
		}
	}

	if (mMoving) {
		mButtonPress = false;
		if (mDashing) {
			if (!(mDashSound.getStatus() == sf::Sound::Playing)) {
				mDashSound.play();
			}
		}
		if (direction == 4 && mPosition.y != newPos.y) {
			mPosition.y -= (1 * mSpeed);
			if (mDashing == true) {
				mAnimationhandler.animation(4, 5, sf::milliseconds(250));
			}
			else if (mPushing) {
				mAnimationhandler.animation(12, 5, sf::milliseconds(100));

			}
			else
				mAnimationhandler.animation(1, 5, sf::milliseconds(100));
		}
		else if (direction == 3 && mPosition.y != newPos.y) {
			mPosition.y += (1 * mSpeed);
			if (mDashing == true) {
				mAnimationhandler.animation(5, 5, sf::milliseconds(250));
			}
			else if (mPushing) {
				mAnimationhandler.animation(13, 5, sf::milliseconds(100));
			}
			else
				mAnimationhandler.animation(0, 5, sf::milliseconds(100));
		}
		else if (direction == 2 && mPosition.x != newPos.x) {
			mPosition.x -= (1 * mSpeed);
			if (mDashing == true) {
				mAnimationhandler.animation(7, 5, sf::milliseconds(250));
			}
			else if (mPushing) {
				mAnimationhandler.animation(14, 5, sf::milliseconds(100));
			}
			else
				mAnimationhandler.animation(3, 5, sf::milliseconds(100));

		}
		else if (direction == 1 && mPosition.x != newPos.x) {
			mPosition.x += (1 * mSpeed);
			if (mDashing == true) {
				mAnimationhandler.animation(6, 5, sf::milliseconds(250));
			}
			else if (mPushing) {
				mAnimationhandler.animation(15, 5, sf::milliseconds(100));
			}
			else
				mAnimationhandler.animation(2, 5, sf::milliseconds(100));
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
			if (mPushing) {
				mPushing = false;
			}
			//mAnimationhandler.reset(direction);
		}
	}
	else if (canMove && !mPushing) // TEMP , SKA ÄNDRAS MED IDLE ANIMATION
	{
		if (direction == 4) {
			if (socksMoved == false) {
				mAnimationhandler.animation(4, 5, sf::milliseconds(250));
			}
			else if (mButtonPress) {
				mAnimationhandler.setFrame(16, 1);
			}
			else
			mAnimationhandler.animation(8, 5, sf::milliseconds(250));
		}
		if (direction == 3) {
			if (socksMoved == false) {
				mAnimationhandler.animation(5, 5, sf::milliseconds(250));
			}
			else if (mButtonPress) {
				mAnimationhandler.setFrame(16, 0);
			}
			else
			mAnimationhandler.animation(9, 5, sf::milliseconds(250));
		}
		if (direction == 2) {
			if (socksMoved == false) {
				mAnimationhandler.animation(7, 5, sf::milliseconds(250));
			}
			else if (mButtonPress) {
				mAnimationhandler.setFrame(16, 2);
			}
			else
			mAnimationhandler.animation(11, 5, sf::milliseconds(250));
		}
		if (direction == 1) {
			if (socksMoved == false) {
				mAnimationhandler.animation(6, 5, sf::milliseconds(250));
			}
			else if (mButtonPress) {
				mAnimationhandler.setFrame(16, 3);
			}
			else
			mAnimationhandler.animation(10, 5, sf::milliseconds(250));
		}
	}
	if (mID == 4 && mObjectThrown) {
		if (ThrownDirection == 4 && ThrownPos.y != newThrownPos.y) {
			ThrownPos.y -= 8;
			//mAnimationhandler.animation(1, 5, sf::milliseconds(100));
		}
		else if (ThrownDirection == 3 && ThrownPos.y != newThrownPos.y) {
			ThrownPos.y += 8;
			//mAnimationhandler.animation(0, 5, sf::milliseconds(100));
		}
		else if (ThrownDirection == 2 && ThrownPos.x != newThrownPos.x) {
			ThrownPos.x -= 8;
			//mAnimationhandler.animation(3, 5, sf::milliseconds(100));

		}
		else if (ThrownDirection == 1 && ThrownPos.x != newThrownPos.x) {
			ThrownPos.x += 8;
			//mAnimationhandler.animation(2, 5, sf::milliseconds(100));
		}
		else
			mObjectThrown = false;
	}
	if (mScooterPrepare && mID == 4) {
		if (mScooterClock.getElapsedTime() > mScooterTime && ScooterRange != 6 && !mSwitch) {
			mScooterTime += sf::milliseconds(500);
			ScooterRange++;
			if (ScooterRange == 6)
				mSwitch = true;
		}
		else if (mScooterClock.getElapsedTime() > mScooterTime && ScooterRange != 1 && mSwitch) {
			mScooterTime += sf::milliseconds(500);
			ScooterRange--;
			cout << ScooterRange << endl;
			if (ScooterRange == 1)
				mSwitch = false;
		}
		rangePos.y = mPosition.y;
		rangePos.x = mPosition.x;
		if (direction == 4) {
			rangePos.y += -(ScooterRange*64) - 64;
		}
		else if (direction == 3) {
			rangePos.y += (ScooterRange * 64) + 64;
		}
		else if (direction == 2) {
			rangePos.x += -(ScooterRange * 64) - 64;
		}
		else if (direction == 1) {
			rangePos.x += (ScooterRange * 64) + 64;
		}
	}
	else {
		rangePos.y = mPosition.y;
		rangePos.x = mPosition.x;
	}
	mAnimationhandler.Update();
}

void Cat::moveForward(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving && canMove) {
		if (mID == 3)
			socksMoved = true;
		direction = 4;
		if (canPushCrate) {
			if (mGrid.moveCrate(this, gridvector(mCoord.x, mCoord.y - 1), tileLayer, Entities)) {
				mPushing = true;
			}
		}
		if (mGrid.isTilePassable(this, gridvector(mCoord.x, mCoord.y - 1), tileLayer, Entities)){
			newPos.y = mPosition.y - 64;
			mMoving = true;
		}
	}
}
void Cat::moveBackWards(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving && canMove) {
		if (mID == 3)
			socksMoved = true;
		direction = 3;

		if (canPushCrate) {
			if (mGrid.moveCrate(this, gridvector(mCoord.x, mCoord.y + 1), tileLayer, Entities)) {
				mPushing = true;
			}
		}

		if (mGrid.isTilePassable(this, gridvector(mCoord.x, mCoord.y + 1), tileLayer, Entities)){
			newPos.y = mPosition.y + 64;
			mMoving = true;
		}
	}
}
void Cat::moveLeft(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving && canMove) {
		if (mID == 3)
			socksMoved = true;
		direction = 2;
		if (canPushCrate) {
			if (mGrid.moveCrate(this, gridvector(mCoord.x - 1, mCoord.y), tileLayer, Entities)) {
				mPushing = true;
			}
		}
		if (mGrid.isTilePassable(this, gridvector(mCoord.x - 1, mCoord.y), tileLayer, Entities)){
			newPos.x = mPosition.x - 64;
			mMoving = true;
		}
	}
}
void Cat::moveRight(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving && canMove) {
		if (mID == 3)
			socksMoved = true;
		direction = 1;
		if (canPushCrate) {
			if (mGrid.moveCrate(this, gridvector(mCoord.x + 1, mCoord.y), tileLayer, Entities)) {
				mPushing = true;
			}
		}
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
	//Socks
	if (mID == 3)
	{
		SocksDistract(tileLayer, Entities, direction);
	}
	if (mID == 4) 
	{
		if (mScooterPrepare && mDelay.restart() > sf::milliseconds(250) && !mCooldown) {
			mScooterPrepare = false;
			cout << "FIRE" << endl;
		}
		else if(!mScooterPrepare && mDelay.restart() > sf::milliseconds(250)&&!mCooldown){
			cout << "HOLD" << endl;
			mScooterPrepare = true;
			mScooterClock.restart();
			mScooterTime = sf::milliseconds(0);
			ScooterRange = 0;
			mSwitch = false;
		}
		 if(!mScooterPrepare)
			ScooterThrow(tileLayer, Entities, direction);
		
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
			if (mCoord == comp->getCoords() && mID == 2 && !mMoving) {
				cout << "Computer gets interacted with!!!!" << endl;
				if (comp->getFace() == "S") {
					mAnimationhandler.playAnimation(4, 6, sf::milliseconds(1000 / 6));
				}
				else if (comp->getFace() == "E") {
					mAnimationhandler.playAnimation(6, 6, sf::milliseconds(1000 / 6));
				}
				else if (comp->getFace() == "W") {
					mAnimationhandler.playAnimation(5, 6, sf::milliseconds(1000 / 6));
				}
				
				comp->playSound();
				canMove = false;
				interactionClock.restart();
				interactionTime = sf::seconds(1);
				comp->Activate(sf::seconds(1));
			}
		}
	}
	if (Button *butt = dynamic_cast<Button*>(usable)) {
		if (mCoord == butt->getCoords() && mID != 3) {
			butt->Activate(sf::seconds(1));
			mButtonPress = true;
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



void Cat::shadowDash(TileLayer *tileLayer, std::vector<Entity*> *Entities, int direc) {
	int positiveNegative = 0;
	int position = 0;
	int positionY = 0;
	int positionX = 0;
	int corrPluY = -(mPosition.y % 64);
	int corrPluX = -(mPosition.x % 64);
	int corrMinY = (mPosition.y % 64);
	int corrMinX = (mPosition.x % 64);

	std::cout << "DASH!" << std::endl;
	if (!mCooldown && !mMoving){  //

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

		/*	std::cout << positionX << std::endl;
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
			}*/

		if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 2), mCoord.y + (positionY * 2)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 3), mCoord.y + (positionY * 3)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 4), mCoord.y + (positionY * 4)), tileLayer, Entities))) {
			std::cout << "4 Tile dash" << std::endl;
			mSpeed = mSpeed * 4;
			position += (256 * positiveNegative);
			positiveNegative *= 3;
			mDashing = true;
			mMoving = true;
			mCooldown = true;
			mAbilityClock.restart();
		}
		else if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 2), mCoord.y + (positionY * 2)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 3), mCoord.y + (positionY * 3)), tileLayer, Entities))) {
			std::cout << "3 Tile dash" << std::endl;
			mSpeed = mSpeed * 4;
			position += (192 * positiveNegative);
			positiveNegative *= 2;
			mDashing = true;
			mMoving = true;
			mCooldown = true;
			mAbilityClock.restart();
		}
		else if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 2), mCoord.y + (positionY * 2)), tileLayer, Entities))) {
			std::cout << "2 Tile dash" << std::endl;
			mSpeed = mSpeed * 4;
			position += (128 * positiveNegative);
			positiveNegative *= 1;
			mDashing = true;
			mMoving = true;
			mCooldown = true;
			mAbilityClock.restart();
		}
		else {
			positiveNegative = 0;
		}

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

Layer Cat::getLayer() {
	return FRONT;
}

// SNOW \\

bool Cat::snowHax(){
	if (mID == 2){
		
		return true;
	}
	else
		return false;
}


// SOCKS \\

void Cat::SocksDistract(TileLayer *tileLayer, std::vector<Entity*> *Entities, int direc)
{
	if (!mCooldown) {
		if (direction == 1 && mGrid.isTilePassable(this, gridvector((mCoord.x + 1), mCoord.y), tileLayer, Entities)) {
			socksMoved = false;
			mSocksDistract = true;
			mSocksCooldown = false;
			mCooldown = true;
		}
		else if (direction == 2 && mGrid.isTilePassable(this, gridvector((mCoord.x - 1), mCoord.y), tileLayer, Entities)) {
			socksMoved = false;
			mSocksDistract = true;
			mSocksCooldown = false;
			mCooldown = true;
		}
		else if (direction == 3 && mGrid.isTilePassable(this, gridvector(mCoord.x, (mCoord.y + 1)), tileLayer, Entities)) {
			socksMoved = false;
			mSocksDistract = true;
			mSocksCooldown = false;
			mCooldown = true;
		}
		else if (direction == 4 && mGrid.isTilePassable(this, gridvector(mCoord.x, (mCoord.y - 1)), tileLayer, Entities)) {
			socksMoved = false;
			mSocksDistract = true;
			mSocksCooldown = false;
			mCooldown = true;
		}
	}
}

void Cat::SetSocksDistract(bool distract)
{
	mSocksDistract = distract;
}

// sCooter \\

#pragma region "Scooter"

void Cat::ScooterThrow(TileLayer *tileLayer, std::vector<Entity*> *Entities, int direc) {
	int positiveNegative = 0;
	int position = 0;
	int positionY = 0;
	int positionX = 0;
	
	//std::cout << "Throw!" << std::endl;
	if (!mCooldown  && !mMoving) {
		if (direction == 1) {
			ThrownDirection = 1;
			positiveNegative = 1;
			positionX = 1;
		}
		else if (direction == 2) {
			ThrownDirection = 2;
			positiveNegative = -1;
			positionX = -1;
		}
		else if (direction == 3) {
			ThrownDirection = 3;
			positiveNegative = 1;
			positionY = 1;
		}
		else if (direction == 4) {
			ThrownDirection = 4;
			positiveNegative = -1;
			positionY = -1;
		}
		mThrow = mCoord;
		ThrownPos = mPosition;
		if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 2), mCoord.y + (positionY * 2)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 3), mCoord.y + (positionY * 3)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 4), mCoord.y + (positionY * 4)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 5), mCoord.y + (positionY * 5)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 6), mCoord.y + (positionY * 6)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 7), mCoord.y + (positionY * 7)), tileLayer, Entities))&& ScooterRange == 6) {
			std::cout << "7 Tile throw" << std::endl;
			position += (448 * positiveNegative);
			positiveNegative *= 7;
			mScooterDistract = true;
			mCooldown = true;
			mObjectThrown = true;
			mAbilityClock.restart();
		}
		else if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 2), mCoord.y + (positionY * 2)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 3), mCoord.y + (positionY * 3)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 4), mCoord.y + (positionY * 4)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 5), mCoord.y + (positionY * 5)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 6), mCoord.y + (positionY * 6)), tileLayer, Entities)) && ScooterRange >= 5) {
			std::cout << "6 Tile throw" << std::endl;
			position += (384 * positiveNegative);
			positiveNegative *= 6;
			mScooterDistract = true;
			mCooldown = true;
			mObjectThrown = true;
			mAbilityClock.restart();
		}
		else if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 2), mCoord.y + (positionY * 2)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 3), mCoord.y + (positionY * 3)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 4), mCoord.y + (positionY * 4)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 5), mCoord.y + (positionY * 5)), tileLayer, Entities)) && ScooterRange >= 4) {
			std::cout << "5 Tile throw" << std::endl;
			position += (320 * positiveNegative);
			positiveNegative *= 5;
			mScooterDistract = true;
			mCooldown = true;
			mObjectThrown = true;
			mAbilityClock.restart();
		}
		else if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 2), mCoord.y + (positionY * 2)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 3), mCoord.y + (positionY * 3)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 4), mCoord.y + (positionY * 4)), tileLayer, Entities)) && ScooterRange >= 3) {
			std::cout << "4 Tile throw" << std::endl;
			position += (256 * positiveNegative);
			positiveNegative *= 4;
			mScooterDistract = true;
			mCooldown = true;
			mObjectThrown = true;
			mAbilityClock.restart();
		}
		else if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 2), mCoord.y + (positionY * 2)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 3), mCoord.y + (positionY * 3)), tileLayer, Entities)) && ScooterRange >= 2) {
			std::cout << "3 Tile throw" << std::endl;
			position += (192 * positiveNegative);
			positiveNegative *= 3;
			mScooterDistract = true;
			mCooldown = true;
			mObjectThrown = true;
			mAbilityClock.restart();
		}
		else if ((mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX), mCoord.y + (positionY)), tileLayer, Entities)) && (mGrid.canCatDash(mCoord, gridvector(mCoord.x + (positionX * 2), mCoord.y + (positionY * 2)), tileLayer, Entities)) && ScooterRange >= 1) {
			std::cout << "2 Tile throw" << std::endl;
			position += (128 * positiveNegative);
			positiveNegative *= 2;
			mScooterDistract = true;
			mCooldown = true;
			mObjectThrown = true;
			mAbilityClock.restart();
		}
		else {
			positiveNegative = 0;
		}
		if (mCooldown == true) {
			canMove = false;
			interactionClock.restart();
			interactionTime = sf::seconds(1.1);
			if (direction == 1) {
				mAnimationhandler.playAnimation(6, 6, sf::milliseconds(1000 / 6));
			}
			else if (direction == 2) {
				mAnimationhandler.playAnimation(7, 6, sf::milliseconds(1000 / 6));
			}
			else if (direction == 3) {
				mAnimationhandler.playAnimation(5, 5, sf::milliseconds(1000 / 5));
			}
			else if (direction == 4) {
				mAnimationhandler.playAnimation(4, 5, sf::milliseconds(1000 / 5));
			}
		}
		if (direc == 1 || direc == 2) {
			newThrownPos.x = ThrownPos.x + position;
			mThrow.x += positiveNegative;
		}
		else {
			newThrownPos.y = ThrownPos.y + position;
			mThrow.y += positiveNegative;
		}
	}
}

gridvector Cat::getThrowPosition() {
	return mThrow;
}

bool Cat::getScooterThrow() {
	return mScooterDistract;
}

void Cat::SetScooterThrow(bool Scooterthrow) {
	mScooterDistract = Scooterthrow;
}
#pragma endregion