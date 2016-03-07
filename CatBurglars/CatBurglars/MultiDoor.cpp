#include "MultiDoor.h"
#include "Channels.h"

MultiDoor::MultiDoor(int channel, int numberofchannels, gridvector coords, sf::Texture *texture,string face) :
mChannel(channel),
mCoords(coords),
mSolid(true),
mFace(face){

	mPosition.x = mCoords.x * 64;
	mPosition.y = mCoords.y * 64;

	mSprite.setTexture(*texture);
	mSprite.setPosition(sf::Vector2f(mPosition.x, mPosition.y - 64));

	if (mFace == "N" || mFace == "S") {
		mSprite.setTextureRect(sf::IntRect(0, 0, 64, 128));
	}
	if (mFace == "W") {
		mSprite.setTextureRect(sf::IntRect(64, 0, 64, 128));
	}
	if (mFace == "E") {
		mSprite.setTextureRect(sf::IntRect(128, 0, 64, 128));
	}

	for (int i = 0; i <= numberofchannels; i++){
		mChannels.push_back(mChannel + i);
	}
}

void MultiDoor::Update(float dt){


	//ifall någon kanal är inaktiv så är dörren stängd
	if (checkChannels()){
		mSolid = false;
	}
	else mSolid = true;
}

bool MultiDoor::checkChannels(){
	for each (int channel in mChannels){
		if (!Channels::isChannelActive(channel)){
			return false;
		}
		
	}

	return true;
}

void MultiDoor::connectToChannel(int channel){
	mChannel = channel;
}

bool MultiDoor::isSolid(){
	return mSolid;
}

sf::Vector2i MultiDoor::GetPosition(){
	return mPosition;
}
gridvector MultiDoor::getCoords(){
	return mCoords;
}

void MultiDoor::Render(sf::RenderWindow *window){
	
	if (mSolid){
		window->draw(mSprite);
	}
}
bool MultiDoor::isInteracting(){
	return false;
}

Layer MultiDoor::getLayer() {
	return DOORS;
}