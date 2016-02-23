#include "Computer.h"
#include "Channels.h"

int COMPUTER_INTERACTION_RADIUS = 20;


Computer::Computer(int channel, sf::Texture *texture, gridvector coords, bool toggle, float holdlength, SoundHandler *soundhandler,string face) :
Usable(),
mChannelID(channel),
mCoords(coords),
mToggle(toggle),
mHoldlength(holdlength),
mSoundHandler(soundhandler),
mFace(face){

	mPosition.x = mCoords.x * 64;
	mPosition.y = mCoords.y * 64;
	if (mFace == "S") {
		mSprite.setTextureRect(sf::IntRect(0 * 64, 0 * 64, 64, 128));
	}
	if (mFace == "E") {
		mSprite.setTextureRect(sf::IntRect(1 * 64, 0 * 64, 64, 128));
	}
	if (mFace == "W") {
		mSprite.setTextureRect(sf::IntRect(2 * 64, 0 * 64, 64, 128));
	}

	
	mSprite.setPosition(sf::Vector2f(mPosition.x,mPosition.y - 64));
	mSprite.setTexture(*texture);

}
bool Computer::isSolid(){
	return false;
}

int Computer::getChannelID(){
	return mChannelID;
}

int computerLength(sf::Vector2i v1, sf::Vector2i v2){
	int length;
	int dx = v2.x - v1.x;
	int dy = v2.y - v1.y;

	length = sqrt((dy * dy) + (dx * dx));
	return length;
}

bool Computer::getInteraction(GameObject *g){
	if (Cat *cat = dynamic_cast<Cat*>(g)){
		if (cat->snowHax()){
			if (computerLength(mPosition, g->GetPosition()) < COMPUTER_INTERACTION_RADIUS && g->isInteracting()){
				// activate channel
				Channels::setActive(mChannelID, mToggle, mHoldlength);
				// play sound
				return true;
			}
		}
	}
}

Layer Computer::getLayer() {
	return OnWallUsables;
}
sf::Vector2i Computer::GetPosition(){
	return mPosition;
}

void Computer::Render(sf::RenderWindow *window){

	window->draw(mSprite);
}
void Computer::Update(float dt){
}
bool Computer::isInteracting(){
	return false;
}
gridvector Computer::getCoords(){
	return mCoords;
}
