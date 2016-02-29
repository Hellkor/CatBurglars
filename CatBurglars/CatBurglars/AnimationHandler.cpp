#include "AnimationHandler.h"
#include <iostream>
AnimationHandler::AnimationHandler(int x, int y, sf::Sprite *sprite) :
mSpriteSizeX(x),
mSpriteSizeY(y),
mSprite(sprite),
mX(0),
mTime(sf::milliseconds(50)){

}

AnimationHandler::~AnimationHandler(){

}

/*void AnimationHandler::forwardAnimation(){
	mSprite->setTextureRect(sf::IntRect(mX * mSpriteSizeX, 2 * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
	if (mClock.getElapsedTime() >= mTime)
	{
		mX++;
		mClock.restart();
	}
	if (mX * mSpriteSizeX >= mSprite->getTexture()->getSize().x)
	{
		mX = 0;
	}
}

void AnimationHandler::backwardsAnimation(){
	mSprite->setTextureRect(sf::IntRect(mX * mSpriteSizeX, 3 * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
	if (mClock.getElapsedTime() >= mTime)
	{
		mX++;
		mClock.restart();
	}

	if (mX * mSpriteSizeX >= mSprite->getTexture()->getSize().x)
	{
		mX = 0;
	}
}

void AnimationHandler::leftAnimation(){
	mSprite->setTextureRect(sf::IntRect(mX * mSpriteSizeX, 0 * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
	if (mClock.getElapsedTime() >= mTime)
	{
		mX++;
		mClock.restart();
	}

	if (mX * mSpriteSizeX >= mSprite->getTexture()->getSize().x)
	{
		mX = 0;
	}
}

void AnimationHandler::rightAnimation(){
	mSprite->setTextureRect(sf::IntRect(mX * mSpriteSizeX, 1 * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
	if (mClock.getElapsedTime() >= mTime)
	{
		mX++;
		mClock.restart();
	}

	if (mX * mSpriteSizeX >= mSprite->getTexture()->getSize().x)
	{
		mX = 0;
	}
		

}
*/
void AnimationHandler::abilityAnimation(){

}

void AnimationHandler::reset(int direction){
	if (!playAnimationBool) {
		if (direction == 1)
			mSprite->setTextureRect(sf::IntRect(0 * mSpriteSizeX, 2 * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
		if (direction == 2)
			mSprite->setTextureRect(sf::IntRect(0 * mSpriteSizeX, 3 * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
		if (direction == 3)
			mSprite->setTextureRect(sf::IntRect(0 * mSpriteSizeX, 0 * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
		if (direction == 4)
			mSprite->setTextureRect(sf::IntRect(0 * mSpriteSizeX, 1 * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));

		mX = 0;
	}
}

void AnimationHandler::animation(int y, int frames, sf::Time time){
	if (!playAnimationBool) {
		mSprite->setTextureRect(sf::IntRect(mX * mSpriteSizeX, y * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
		if (mClock.getElapsedTime() >= time)
		{
			mX++;
			mClock.restart();
		}

		if (mX >= frames)
		{
			mX = 0;
		}

	}
	
}

void AnimationHandler::Update() {

	if (playAnimationBool) {
		
		
		
		if (mClock.getElapsedTime() >= mTime && mX < mMaxFrames)
		{
			mSprite->setTextureRect(sf::IntRect(mX * mSpriteSizeX, mYOffset * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
			std::cout << "nextframe" << std::endl;
			mX++;
			mClock.restart();
		}

		if (mX >= mMaxFrames)
		{
			std::cout << "reset" << std::endl;
			playAnimationBool = false;
			mX = 0;
		}
		

	}
}

void AnimationHandler::playAnimation(int y, int frames, sf::Time time){
	if (!playAnimationBool) {
		mYOffset = y;
		mMaxFrames = frames;
		mTime = time;
		playAnimationBool = true;
		//mSprite->setTextureRect(sf::IntRect(mX * mSpriteSizeX, y * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
		
	}
}

void AnimationHandler::setFrame(int y, int x)
{
	mSprite->setTextureRect(sf::IntRect(x * mSpriteSizeX, y * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
}
