#include "Lazer.h"




Lazer::Lazer(int channel, int channelRange, gridvector coords, sf::Texture *texture, int range, string face) :
	mChannel(channel),
		mCoords(coords),
		isOn(true),
		mFace(face) {

		for (int i = 0; i <= channelRange; i++) {
			mChannels.push_back(mChannel + i);
		}

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
		TextureHandler textures;
		mSprite.setTexture(*texture);
		mSprite.setTextureRect(sf::IntRect((direction - 1) * 64, 0, 64, 64));
		mSprite.setPosition((sf::Vector2f)mPosition);
		textures.Initialize();

		mHitboxSprite.setTexture(*textures.GetTexture(99));


		int width = 1;
		int height = 0;

		if (mFace == "N") {
			for (int i = 0; i <= range; i++) {
				mVision.push_back(new gridvector(mCoords.x, mCoords.y - i));
			}
		}
		if (mFace == "S") {
			for (int i = 0; i <= range; i++) {

				mVision.push_back(new gridvector(mCoords.x, mCoords.y + i));
			}
		}
		if (mFace == "E") {
			for (int i = 0; i <= range; i++) {

				mVision.push_back(new gridvector(mCoords.x + i, mCoords.y));
			}
		}
		if (mFace == "W") {
			for (int i = 0; i <= range; i++) {

				mVision.push_back(new gridvector(mCoords.x - i, mCoords.y));

				}
			}


mConvex.setTexture(textures.GetTexture(99));
	}
	


Lazer::~Lazer() {

}

bool Lazer::checkChannels() {
	for each (int channel in mChannels) {
		if (!Channels::isChannelActive(channel)) {
			return false;
		}

	}

	return true;
}

void Lazer::Update(float dt) {

	//ifall någon kanal är inaktiv så är dörren stängd
	if (checkChannels()) {
		isOn = false;
	}
	else isOn = true;
}

void Lazer::connectToChannel(int channel) {
	mChannel = channel;
}
bool Lazer::getIntersection(GameObject *obj) {
	if (isOn) {
		for each (gridvector *v in mVision) {
			if (obj->getCoords() == v) {
				return true;
			}
		}
	}
	return false;
}






sf::Vector2i Lazer::GetPosition() {
	return mPosition;
}



gridvector Lazer::getCoords() {
	return mCoords;
}

sf::Vector2i Lazer::getDirection() {
	return mDirection;
}




void Lazer::Render(sf::RenderWindow *window) {
	window->draw(mSprite);

	if (isOn) {
		
		for each (gridvector *v in mVision) {
			mHitboxSprite.setPosition(v->x * 64, v->y * 64);

			window->draw(mHitboxSprite);
		}
	}



}

bool Lazer::isInteracting() {
	return false;
}

bool Lazer::isSolid() {
	return false;
}

Layer Lazer::getLayer() {
	return FRONT;
}