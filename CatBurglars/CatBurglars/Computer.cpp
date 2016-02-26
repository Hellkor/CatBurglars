#include "Computer.h"
#include "Channels.h"
#include "Cat.h"

int COMPUTER_INTERACTION_RADIUS = 20;


Computer::Computer(int channel, sf::Texture *texture, gridvector coords, bool toggle, float holdlength, SoundHandler *soundhandler,string face) :
Usable(),
mChannelID(channel),
mCoords(coords),
mToggle(toggle),
mHoldlength(holdlength),
mSoundHandler(soundhandler),
mFace(face){
	mInteractedSound.setBuffer(*mSoundHandler->getSound(3));
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
				//mSoundHandler->PlaySound(3);
				//mInteractedSound.play(); 
				Channels::setActive(mChannelID, mToggle, mHoldlength);
				// play sound
				return true;
			}
		}
	}
}

bool Computer::Activate(sf::Time active_time) {
	if (!gettingHacked) {
		activateDelay = active_time;
		activateClock.restart();
		gettingHacked = true;
		return true;
	}
	else return false;
}
bool Computer::playSound() {
	return true;
}
void Computer::activateChannel() {
	Channels::setActive(mChannelID, mToggle, mHoldlength);
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
	if (gettingHacked) {
		if (activateClock.getElapsedTime().asSeconds() > activateDelay.asSeconds()) {
			gettingHacked = false;
			activateChannel();
		}
	}
}
bool Computer::isInteracting(){
	return false;
}
gridvector Computer::getCoords(){
	return mCoords;
}
