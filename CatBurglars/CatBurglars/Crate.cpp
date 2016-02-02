#include "Crate.h"

int INTERACTION_RADIUSS_CRATE = 64;

Crate::Crate(sf::Texture *texture, gridvector position, int ID): GameObject(),
mID(ID),
mCoord(position){
	mSprite.setTexture(*texture, true);

	mPosition = sf::Vector2i(mCoord.x * 64, mCoord.y * 64);
}

Crate::~Crate(){

}

void Crate::Render(sf::RenderWindow *mainWindow){
	mSprite.setPosition((sf::Vector2f)mPosition);
	mainWindow->draw(mSprite);
}

void Crate::Update(){

}

sf::Vector2i Crate::GetPosition(){
	return mPosition;
}

void Crate::moveForward() {
	if (!mMoving) {
		// if (!Grid.getTile(mCoords.x -1,mCoords.y)->isSolid())
		// do....
		newPos.y = mPosition.y - 64;
		direction = 4;
		c.restart();
		mCoord.y--;
		mMoving = true;
	}
}
void Crate::moveBackWards() {
	if (!mMoving) {
		newPos.y = mPosition.y + 64;
		direction = 3;
		c.restart();
		mCoord.y++;
		mMoving = true;
	}
}
void Crate::moveLeft() {
	if (!mMoving) {

		newPos.x = mPosition.x - 64;
		direction = 2;
		c.restart();
		mCoord.x--;
		mMoving = true;
	}
}
void Crate::moveRight() {
	if (!mMoving) {
		newPos.x = mPosition.x + 64;
		direction = 1;
		c.restart();
		mCoord.x++;
		mMoving = true;
	}
}

int lengthCrate(sf::Vector2i v1, sf::Vector2i v2){
	int length;
	int dx = v2.x - v1.x;
	int dy = v2.y - v1.y;

	length = sqrt((dy * dy) + (dx * dx));
	return length;
}

bool Crate::getInteraction(Cat *cat){

	if (lengthCrate(mPosition, cat->GetPosition()) < INTERACTION_RADIUSS_CRATE){
		//if (cat->interacting()){

		// play sound
		return true;
		}

}