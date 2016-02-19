#include "Collectible.h"

Collectible::Collectible(sf::Texture *texture, gridvector position, bool collected) : GameObject(),
mCoords(position),
mCollected(collected){
	mSprite.setTexture(*texture, true);
	//Starting position
	mPosition = sf::Vector2i(mCoords.x*64, mCoords.y*64);
	mSprite.setPosition(mCoords.x * 64, mCoords.y * 64);
}

Collectible::~Collectible() {

}

//Render sprite on screen
void Collectible::Render(sf::RenderWindow *mainWindow){

	if (!mCollected) {
		mainWindow->draw(mSprite);
	}
}

void Collectible::Update(float dt){
	
}


bool Collectible::isInteracting(){
	return false;
}

Layer Collectible::getlayer() {
	return BACK;
}
bool Collectible::isSolid(){
	return false;
}

//Returns position of sprite
sf::Vector2i Collectible::GetPosition(){
	return mPosition;
}
gridvector Collectible::getCoords(){
	return mCoords;
}

bool Collectible::getInteraction(Cat *cat) {
	if (cat->getCoords() == mCoords) {
		mCollected = true;
		return true;
	}
	else
		return false;
}


