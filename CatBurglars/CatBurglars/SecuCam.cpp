#include "secuCam.h"
#include "TextureHandler.h"

TextureHandler textures;
secuCam::secuCam(int channel, gridvector coords, sf::Texture *texture,int range) :
mChannel(channel),
mCoords(coords){

	mPosition.x = mCoords.x * 64;
	mPosition.y = mCoords.y * 64;

	mSprite.setTexture(*texture);
	mSprite.setPosition((sf::Vector2f)mPosition);

	textures.Initialize();

	knark.setTexture(*textures.GetTexture(99));


	int width = 0;

	for (int i = 0; i <= range ; i++){

		mVision.push_back(new gridvector(mCoords.x,mCoords.y - i));
		
		for (int j = 0; j < width; j++){
			cout << "asofd" << endl;
			mVision.push_back(new gridvector(mCoords.x + j, mCoords.y - i));
			mVision.push_back(new gridvector(mCoords.x + -j, mCoords.y - i));
		}

			width++;
	}


}
secuCam::~secuCam(){
	mVision.clear();
}

void secuCam::Update(float dt){
	if (Channels::isChannelActive(mChannel)){ 	isOn = false;	}
}

void secuCam::connectToChannel(int channel){
	mChannel = channel;
}
bool secuCam::getIntersection(GameObject *obj){

	for each (gridvector *v in mVision){
		if (obj->getCoords() == v){
			return true;
		}
	}

	return false;
}




sf::Vector2i secuCam::GetPosition(){
	return mPosition;
}



gridvector secuCam::getCoords(){
	return mCoords;
}

sf::Vector2i secuCam::getDirection(){
	return mDirection;
}




void secuCam::Render(sf::RenderWindow *window){
	window->draw(mSprite);
	for each (gridvector *v in mVision){
		knark.setPosition(v->x * 64, v->y * 64);
		window->draw(knark);
	}
}

bool secuCam::isInteracting(){
	return false;
}

bool secuCam::isSolid(){
	return true;
}


/*
bool secuCam::isOn(){
if (mChannel.isActive){
mOn != isOn
}
*/ //växlar mellan av/på
