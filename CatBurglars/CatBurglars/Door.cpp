#include "Door.h"

Door::Door(int channel, gridvector coords, sf::Texture *texture, SoundHandler *soundhandler):
	mChannel(channel),
	mCoords(coords),
	mSoundHandler(soundhandler){

	mPosition.x = mCoords.x * 64;
	mPosition.y = mCoords.y * 64;

	mSprite.setTexture(*texture);
	mSprite.setPosition(sf::Vector2f(mPosition.x,mPosition.y - 64));
}

void Door::Update(float dt){

	if (Channels::isChannelActive(mChannel)){
		mSolid = false;
	}
	else mSolid = true;
}
Layer Door::getLayer() {
	return DOORS;
}
void Door::connectToChannel(int channel){
	mChannel = channel;
}

bool Door::isSolid(){
	return mSolid;
}

sf::Vector2i Door::GetPosition(){
	return mPosition;
}
gridvector Door::getCoords(){
	return mCoords;
}

void Door::Render(sf::RenderWindow *window){

	if (mSolid){
		window->draw(mSprite);
	}
}
bool Door::isInteracting(){
	return false;
}