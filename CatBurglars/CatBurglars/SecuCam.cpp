#include "secuCam.h"
#include "TextureHandler.h"
TextureHandler textures;

secuCam::secuCam(int channel, int channelRange, gridvector coords, sf::Texture *texture, int range, string face) :
mChannel(channel),
mCoords(coords),
isOn(true),
mFace(face){


	for (int i = 0; i <= channelRange; i++) {
		mChannels.push_back(mChannel + i);
	}
	// mConvex for visionrange visual effect
	mConvex.setPointCount(3);

	mPosition.x = mCoords.x * 64;
	mPosition.y = mCoords.y * 64;
	int direction;
	if (mFace == "N") {
		direction = 1;
	}
	if (mFace == "S") {
		direction = 2;
	}
	if (mFace == "E") {
		direction = 3;
	}
	if (mFace == "W") {
		direction = 4;
	}
	
	mSprite.setTexture(*texture);
	mSprite.setTextureRect(sf::IntRect((direction-1) * 64, 0, 64, 64));
	mSprite.setPosition((sf::Vector2f)mPosition);
	textures.Initialize();

	mHitboxSprite.setTexture(*textures.GetTexture(99));
	

	int width = 1;
	int height = 0;

	if (mFace == "N"){
		for (int i = 0; i <= range; i++){
			mVision.push_back(new gridvector(mCoords.x, mCoords.y - i));

			for (int j = 1; j < width; j++){
				mVision.push_back(new gridvector(mCoords.x + j, mCoords.y - i));
				mVision.push_back(new gridvector(mCoords.x + -j, mCoords.y - i));
			}

			width++;
		}
		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
		// define the points
		mConvex.setPoint(0, sf::Vector2f(conePos.x, conePos.y));
		mConvex.setPoint(1, sf::Vector2f(conePos.x - 32 - (width-2) * 64, conePos.y - 32 - range * 64));
		mConvex.setPoint(2, sf::Vector2f(conePos.x + 32 + (width-2) * 64, conePos.y - 32 - range * 64));
	}
	if (mFace == "S"){
		for (int i = 0; i <= range; i++){

			mVision.push_back(new gridvector(mCoords.x, mCoords.y + i));

			for (int j = 1; j < width; j++){
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
	if (mFace == "E"){
		for (int i = 0; i <= range; i++){

			mVision.push_back(new gridvector(mCoords.x + i, mCoords.y ));

			for (int j = 1; j < width; j++){
				mVision.push_back(new gridvector(mCoords.x + i, mCoords.y + j));
				mVision.push_back(new gridvector(mCoords.x + i, mCoords.y - j));
			}

			width++;
		}

		sf::Vector2f conePos(mPosition.x + 32, mPosition.y + 32);
		// define the points
		mConvex.setPoint(0, sf::Vector2f(conePos.x, conePos.y));
		mConvex.setPoint(1, sf::Vector2f(conePos.x + 32 + range * 64, conePos.y - 32 -(width - 2) * 64));
		mConvex.setPoint(2, sf::Vector2f(conePos.x + 32 + range * 64, conePos.y + 32 +(width - 2) * 64));
	}
	if (mFace == "W"){
		for (int i = 0; i <= range; i++){

			mVision.push_back(new gridvector(mCoords.x - i, mCoords.y));

			for (int j = 1; j < width; j++){
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
	
	mConvex.setTexture(textures.GetTexture(99));
}
secuCam::~secuCam(){
	
}
bool secuCam::checkChannels() {
	for each (int channel in mChannels) {
		if (!Channels::isChannelActive(channel)) {
			return false;
		}

	}

	return true;
}
void secuCam::Update(float dt){

	//ifall någon kanal är inaktiv så är dörren stängd
	if (checkChannels()) {
		isOn = false;
	}
	else isOn = true;
}

void secuCam::connectToChannel(int channel){
	mChannel = channel;
}
bool secuCam::getIntersection(GameObject *obj){
	if (isOn){
		for each (gridvector *v in mVision){
			if (obj->getCoords() == v){
				return true;
			}
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
	
	if (isOn){
		window->draw(mConvex);
		for each (gridvector *v in mVision){
			mHitboxSprite.setPosition(v->x * 64, v->y * 64);
			
			//window->draw(mHitboxSprite);
		}
	}

	
	
}

bool secuCam::isInteracting(){
	return false;
}

bool secuCam::isSolid(){
	return false;
}

Layer secuCam::getLayer() {
	return FRONT;
}