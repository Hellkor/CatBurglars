#include "secuCam.h"

secuCam::secuCam(int channel, gridvector coords, sf::Texture *texture) :
mChannel(channel),
mCoords(coords){

	mPosition.x = mCoords.x * 64;
	mPosition.y = mCoords.y * 64;

	mSprite.setTexture(*texture);
	mSprite.setPosition((sf::Vector2f)mPosition);
}

void secuCam::Update(float dt){
	if (Channels::isChannelActive(mChannel)){
		isOn = false;
	}
}

void secuCam::connectToChannel(int channel){
	mChannel = channel;
}

sf::Vector2i secuCam::GetPosition(){
	return mPosition;
}

void secuCam::Render(sf::RenderWindow *window){

}

bool secuCam::isInteracting(){
	return false;
}

/*
bool secuCam::isOn(){
	if (mChannel.isActive){
	mOn != isOn
}
*/ //v�xlar mellan tv� texturer