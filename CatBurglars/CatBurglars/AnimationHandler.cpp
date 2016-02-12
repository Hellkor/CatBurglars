#include "AnimationHandler.h"

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
	if (direction == 1)
		mSprite->setTextureRect(sf::IntRect(0 * mSpriteSizeX, 2 * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
	if (direction == 2)
		mSprite->setTextureRect(sf::IntRect(0 * mSpriteSizeX, 3 * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
	if (direction == 3)
		mSprite->setTextureRect(sf::IntRect(0 * mSpriteSizeX, 0 * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
	if (direction == 4)
		mSprite->setTextureRect(sf::IntRect(0 * mSpriteSizeX, 1 * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
}

void AnimationHandler::animation(int y, int frames, sf::Time time){
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

void AnimationHandler::playAnimation(int y, int frames, sf::Time time){
	mSprite->setTextureRect(sf::IntRect(mX * mSpriteSizeX, y * mSpriteSizeY, mSpriteSizeX, mSpriteSizeY));
	if (mClock.getElapsedTime() >= time && mX < frames)
	{
		mX++;
		mClock.restart();
	}
}