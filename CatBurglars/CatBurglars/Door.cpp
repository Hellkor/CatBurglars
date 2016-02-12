#include "Door.h"

Door::Door(int channel, gridvector coords, sf::Texture *texture):
	mChannel(channel),
	mCoords(coords){

	mPosition.x = mCoords.x * 64;
	mPosition.y = mCoords.y * 64;

	mSprite.setTexture(*texture);
	mSprite.setPosition((sf::Vector2f)mPosition);
}

void Door::Update(float dt){

	if (Channels::isChannelActive(mChannel)){
		mSolid = false;
	}
	else mSolid = true;
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